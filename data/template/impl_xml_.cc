<?xml version="1.0"?>
<peppher:component xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
 xmlns:peppher="http://www.peppher.eu/ComponentMetaData0.1" 
 xsi:schemaLocation="http://www.peppher.eu/ComponentMetaData0.1 ComponentMetaData.xsd" >

<peppher:implementation name=" $IMPNAME ">
   <peppher:sourceFiles>
        <peppher:sourceFile name=" $FILENAME " version="1.0" language="C">
			<peppher:compilation>
				<peppher:compiler>
					<peppher:name> $COMPILERNAME </peppher:name>
					<peppher:version> </peppher:version>
					<peppher:flags> </peppher:flags>
				</peppher:compiler>
                <peppher:language> C++ </peppher:language>
			</peppher:compilation>
        </peppher:sourceFile>
	</peppher:sourceFiles>

<peppher:providedInterfaces>
<peppher:providedInterface name=" $INFNAME ">
</peppher:providedInterface>
</peppher:providedInterfaces>

<peppher:targetPlatform name=" $IMPTYPE ">
</peppher:targetPlatform>

</peppher:implementation>
</peppher:component>