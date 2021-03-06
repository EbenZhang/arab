# Generated by the protocol buffer compiler.  DO NOT EDIT!

from google.protobuf import descriptor
from google.protobuf import message
from google.protobuf import reflection
from google.protobuf import descriptor
# @@protoc_insertion_point(imports)



DESCRIPTOR = descriptor.FileDescriptor(
  name='arab/types.proto',
  package='Arab',
  serialized_pb='\n\x10\x61rab/types.proto\x12\x04\x41rab\"e\n\tErrorCode\x12,\n\nerror_code\x18\x01 \x02(\x0e\x32\x14.Arab.ErrorCode.Code:\x02OK\"*\n\x04\x43ode\x12\x06\n\x02OK\x10\x00\x12\x0c\n\x08TIME_OUT\x10\x01\x12\x0c\n\x08NOT_IMPL\x10\x02\"Z\n\tTunnelMsg\x12\x1e\n\x05\x65rror\x18\x01 \x02(\x0b\x32\x0f.Arab.ErrorCode\x12\x14\n\x0cmessage_type\x18\x02 \x02(\t\x12\x17\n\x0fmessage_content\x18\x03 \x01(\x0c\")\n\x07\x45rrResp\x12\x1e\n\x05\x65rror\x18\x01 \x02(\x0b\x32\x0f.Arab.ErrorCode')



_ERRORCODE_CODE = descriptor.EnumDescriptor(
  name='Code',
  full_name='Arab.ErrorCode.Code',
  filename=None,
  file=DESCRIPTOR,
  values=[
    descriptor.EnumValueDescriptor(
      name='OK', index=0, number=0,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='TIME_OUT', index=1, number=1,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='NOT_IMPL', index=2, number=2,
      options=None,
      type=None),
  ],
  containing_type=None,
  options=None,
  serialized_start=85,
  serialized_end=127,
)


_ERRORCODE = descriptor.Descriptor(
  name='ErrorCode',
  full_name='Arab.ErrorCode',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    descriptor.FieldDescriptor(
      name='error_code', full_name='Arab.ErrorCode.error_code', index=0,
      number=1, type=14, cpp_type=8, label=2,
      has_default_value=True, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
    _ERRORCODE_CODE,
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  serialized_start=26,
  serialized_end=127,
)


_TUNNELMSG = descriptor.Descriptor(
  name='TunnelMsg',
  full_name='Arab.TunnelMsg',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    descriptor.FieldDescriptor(
      name='error', full_name='Arab.TunnelMsg.error', index=0,
      number=1, type=11, cpp_type=10, label=2,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='message_type', full_name='Arab.TunnelMsg.message_type', index=1,
      number=2, type=9, cpp_type=9, label=2,
      has_default_value=False, default_value=unicode("", "utf-8"),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='message_content', full_name='Arab.TunnelMsg.message_content', index=2,
      number=3, type=12, cpp_type=9, label=1,
      has_default_value=False, default_value="",
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  serialized_start=129,
  serialized_end=219,
)


_ERRRESP = descriptor.Descriptor(
  name='ErrResp',
  full_name='Arab.ErrResp',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    descriptor.FieldDescriptor(
      name='error', full_name='Arab.ErrResp.error', index=0,
      number=1, type=11, cpp_type=10, label=2,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  serialized_start=221,
  serialized_end=262,
)

_ERRORCODE.fields_by_name['error_code'].enum_type = _ERRORCODE_CODE
_ERRORCODE_CODE.containing_type = _ERRORCODE;
_TUNNELMSG.fields_by_name['error'].message_type = _ERRORCODE
_ERRRESP.fields_by_name['error'].message_type = _ERRORCODE
DESCRIPTOR.message_types_by_name['ErrorCode'] = _ERRORCODE
DESCRIPTOR.message_types_by_name['TunnelMsg'] = _TUNNELMSG
DESCRIPTOR.message_types_by_name['ErrResp'] = _ERRRESP

class ErrorCode(message.Message):
  __metaclass__ = reflection.GeneratedProtocolMessageType
  DESCRIPTOR = _ERRORCODE
  
  # @@protoc_insertion_point(class_scope:Arab.ErrorCode)

class TunnelMsg(message.Message):
  __metaclass__ = reflection.GeneratedProtocolMessageType
  DESCRIPTOR = _TUNNELMSG
  
  # @@protoc_insertion_point(class_scope:Arab.TunnelMsg)

class ErrResp(message.Message):
  __metaclass__ = reflection.GeneratedProtocolMessageType
  DESCRIPTOR = _ERRRESP
  
  # @@protoc_insertion_point(class_scope:Arab.ErrResp)

# @@protoc_insertion_point(module_scope)
