// 32 bits

define all
   x/16i $eip
   echo \n
   i r
   echo \n
   x/40wx $esp
end

define nall
   set $instr=$eip
   ni
   x/i $instr
   all
end

set disassembly-flavor intel

// OR 64bits

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
