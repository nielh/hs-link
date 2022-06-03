# Introduction
HS-Link is cmsis-dap v2.0 debug adapter firmware on CH32V307VCT6,
support High speed USB 2.0(480M) winusb bulk, Max SWD clock about 24Mhz

# How to get firmawre
You can build firmawre from source, open HS-LINK.wvproj project with MounDriver and build all,then download into your board
or use my binary [obj/HS-LINK.hex], download it with WCHISPTool

# How to use HS-LINK adapter

1. Connect HS-LINK to your board
		(HS-LINK)PA0 ---------> (your board)SWCLK
		(HS-LINK)PA1 <--------> (your board)SWDIO
		(HS-LINK)PA2 ---------> (your board)nSRST(option)

2. Plugin HS-LINK to pc USB 2.0 port
3. Open your arm project with MDK
4. Select your arm project target debugger as HS-LINK CMSIS-DAP in target options dialog
        select Port is SW, 
        select max clock you want (MDK cannot choose max clock 24M, The 5K effect is 24M )
5. Ctrl+F5 or click Start Debug Session Button

Good luck :)

