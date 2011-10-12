#!/usr/bin/env python

__author__ = 'zhangyingneng'

#coding=utf-8
class TimeoutError(Exception):
    '''TimeoutError exception class for RPC protocol buffer errors.'''

    def __init__(self):
        '''TimeoutError constructor.

        message - Message string detailing error.
        '''
        self.message = "timeout"
  