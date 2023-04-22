# ModifyTLSCallbacks
Edit the program's TLS callbacks at runtime (anti-debugging method)  

The debugger will try to parse our modified TLS callback pointer when we change it to the same address as the image base, resulting in the debugger failing to load. Tested and working with x64dbg, and CE debugger. Please see ModifyTLSCallbacks.cpp for a simple example.
