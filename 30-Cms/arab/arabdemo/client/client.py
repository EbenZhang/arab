#!/usr/bin/env python
#coding=utf-8

__author__ = 'zhangyingneng'
import sys

from arabpy.channel import Channel
from echo import *
from arab.error import TimeoutError
import arab.reflection

server_address = "tcp://127.0.0.1:5555"
rpc_channel = Channel(server_address)
client = EchoService_Stub(rpc_channel)

req = EmptyMessage()

try:
    rep = client.EchoTunnelMsg(0,req,0)
    obj = arab.reflection.create_obj(rep.message_type)
    obj.ParseFromString(rep.message_content)
    print obj.response
except TimeoutError:
    print 'timeout'


