define all
   x/4i $rip
   echo \n
   i r
   echo \n
   x/32wx $rsp
end

define nall
   set $instr=$rip
   ni
   x/i $instr
   all
end

set disassembly-flavor intel