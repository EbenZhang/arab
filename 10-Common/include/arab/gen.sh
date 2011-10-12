cd ..
protoc arab/types.proto --cpp_out=./ --python_out=./
cd arab
mv ./types.pb.cc ../../../30-Cms/arab/arabcpp/src/types.pb.cc
sed -i 's/_pb2//g' ./types_pb2.py
mv ./types_pb2.py ../../../30-Cms/arab/arabpy/arab/types.py
