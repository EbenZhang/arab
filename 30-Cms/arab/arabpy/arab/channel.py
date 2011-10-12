#!/usr/bin/env python
#coding=utf-8

from google.protobuf.service import *
import zmq
import error
import types

class Channel(RpcChannel):
    def __init__(self,server_address,timeout = 10000):
        '''server_address: base on zmq protocol, eg.tcp://127.0.0.1:5555
        timeout:     in milliseconds
        '''
        self.zmq_ctx = zmq.Context()
        self.rpc_socket = self.zmq_ctx.socket(zmq.REQ)
        self.rpc_socket.connect(server_address)
        self.timeout = timeout
    def CallMethod(self, method_descriptor, rpc_controller,
                 request, response_class, done):
        self.rpc_socket.send(method_descriptor.full_name +
                             '\0' +
                             request.SerializeToString())
        poller = zmq.Poller()
        poller.register(self.rpc_socket,zmq.POLLIN)
        sockets = dict(poller.poll(self.timeout))

        if self.rpc_socket in sockets:
            data = self.rpc_socket.recv()

            dummyResp = types.ErrResp()

            dummyResp.ParseFromString(data)
            if dummyResp.error.error_code != types.ErrorCode.OK:
                return dummyResp

            response = response_class()
            response.ParseFromString(data)
        else:
            #time for msg stay in the queue
            self.rpc_socket.setsockopt(zmq.LINGER, 0)
            self.rpc_socket.close()
            dummyResp = types.ErrResp()
            dummyResp.error.error_code = types.ErrorCode.TIME_OUT
            return dummyResp

        response.error.error_code = types.ErrorCode.OK
        return response


