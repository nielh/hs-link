# Introduction
HS-Link is cmsis-dap v2.0 firmware on CH32V307VCT6,
support USB 2.0 High speed(480M) winusb bulk, Max SWD clock about 24Mhz

# How to get firmawre
You can build firmware from source, open HS-LINK.wvproj project with MounRiver and build all,then download into your probe board
or you can use my hex file [obj/HS-LINK.hex], download it with WCHISPTool to your probe board


# How to use HS-LINK adapter

1. Connect HS-LINK to your board

		(HS-LINK)PA0 ---------> (your arm board)SWCLK
		(HS-LINK)PA1 <--------> (your arm board)SWDIO
		(HS-LINK)PA2 ---------> (your arm board)nSRST(option)

2. Plugin HS-LINK to pc USB 2.0 port
3. Open your arm project with MDK
4. Select your arm project target debugger as HS-LINK CMSIS-DAP in target options dialog
        select Port is SW, 
        select max clock you want (MDK cannot choose max clock 24M, `The 5K effect is 24M` )
5. Ctrl+F5 or Click Start Debug Session Button

Good luck :)

