#!/usr/bin/env python
#coding=utf-8

__author__ = 'zhangyingneng'
import sys

from arab.channel import Channel
from echo import *
from arab.error import TimeoutError
import arab.reflection

server_address = "tcp://127.0.0.1:5555"
rpc_channel = Channel(server_address)
client = EchoService_Stub(rpc_channel)

req = EchoRequest()
req.message = 'hello'

try:
    rep = client.Echo(0,req,0)
    print rep.response
except TimeoutError:
    print 'timeout'


