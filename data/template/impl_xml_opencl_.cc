<?xml version="1.0"?>
<peppher:component xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
 xmlns:peppher="http://www.peppher.eu/ComponentMetaData0.1" 
 xsi:schemaLocation="http://www.peppher.eu/ComponentMetaData0.1 ComponentMetaData.xsd" >

<peppher:implementation name=" $IMPNAME ">
   <peppher:sourceFiles>
        <peppher:sourceFile name=" $FILENAME " version="1.0" language="OpenCL" starpu_opencl_program=" $CLNAME " cl_kernel=" $KRHNAME " cl_command_queue=" $QUNAME ">
			<peppher:compilation>
				<peppher:compiler>
					<peppher:name> g++ </peppher:name>
					<peppher:version> </peppher:version>
					<peppher:flags> </peppher:flags>
				</peppher:compiler>
                <peppher:language> OpenCL </peppher:language>
			</peppher:compilation>
        </peppher:sourceFile>
		 <peppher:sourceFile name=" $CLFILENAME " kernel=" $KRNAME " version="1.0" language="OpenCL" >
		 <peppher:compilation>
				
		 </peppher:compilation>
        </peppher:sourceFile>
	</peppher:sourceFiles>

<peppher:providedInterfaces>
<peppher:providedInterface name=" $INFNAME ">
</peppher:providedInterface>
</peppher:providedInterfaces>

<peppher:targetPlatform name=" OpenCL ">
</peppher:targetPlatform>

</peppher:implementation>
</peppher:component>