#!/usr/bin/env python

__author__ = 'zhangyingneng'

#coding=utf-8

def _reflect_class_and_import(name):
    class_name = name
    mod_name = ''
    if '.' in name:
        splitter = name.split('.')
        class_name = splitter[-1]

        mod_name = name[0:name.rfind('.')]
        
    mod = __import__(mod_name)

    return getattr(mod, class_name)

def create_obj(class_name):
    '''
    create object base on the class_name
    '''
    the_class = _reflect_class_and_import(class_name)
    return the_class()
