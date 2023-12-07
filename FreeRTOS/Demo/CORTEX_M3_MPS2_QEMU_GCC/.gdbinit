target remote localhost:12345
set pagination off
set logging on
file build/RTOSDemo.axf
set confirm off

define es
 stepi
 disas $pc,+10
end
