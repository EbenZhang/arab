#!/bin/bash
mkdir -p ./out
protoc echo.proto -I../../../10-Common/include/ -I./ --cpp_out=./out --python_out=./out
mv ./out/echo.pb.* ./server/
sed -i 's/_pb2//g' ./out/echo_pb2.py
cp ./out/echo_pb2.py ./client/echo.py
mv ./out/echo_pb2.py ../../pmc/echo.py
