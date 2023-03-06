#treat header
#f = open ("botan_all.h","rb")
#data = f.read()
#f.close();
#
#data = data.replace("const throw()", "// const throw()");
#
#f = open("botan_all.h","wb");
#f.write(data);
#f.close();

#treat source
f = open ("botan_all.cpp","r")
data = f.read()
f.close()

#data = data.replace("throw;", "throw _details::_fake_exception(__FUNCTION__);");
#data = data.replace("throw Mutex_State_Error(", "throw _details::_fake_exception(");
data = data.replace("e.what()", "__FUNCTION__")
data = data.replace("error_type = e.type();", "error_type = NO_ALERT_TYPE;")

f = open("botan_all.cpp","w")
f.write(data)
f.close()
