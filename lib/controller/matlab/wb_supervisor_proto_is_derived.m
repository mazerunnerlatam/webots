function result = wb_supervisor_proto_is_derived(protoref)
% Usage: wb_supervisor_proto_is_derived(protoref)
% Matlab API for Webots
% Online documentation is available <a href="https://www.cyberbotics.com/doc/reference/supervisor">here</a>

result = calllib('libController', 'wb_supervisor_proto_is_derived', protoref);
