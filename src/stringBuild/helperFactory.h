#ifndef HELPERFACTORY_
#define HELPERFACTORY_

#include <iostream>
#include <Helper.h>
#include <IMNP1.h>
#include <SN1.h>
#include <TYPE1.h>
#include <Cap.h>
#include <CCCS2.h>
#include <CCQN2.h>
#include <CLNB2.h>
#include <CKN2.h>
#include <CLBN2.h>
#include <CLF2.h>
#include <CLN2.h>
#include <CLRL2.h>
#include <CLTB2.h>
#include <TASKSYNC.h>
#include <CUCC2.h>
#include <DRS2.h>
#include <EF2.h>
#include <EXTS.h>
#include <EXTSU.h>
#include <HD2.h>
#include <IMND1.h>
#include <INWQM2.h>
#include <IMNO1.h>
#include <IMNWD1.h>
#include <IMNWO1.h>
#include <IMNWP1.h>
#include <IMPA1.h>
#include <PCD1.h>
#include <IN1.h>
#include <INCS.h>
#include <INCSU.h>
#include <INWC2.h>
#include <INSTCL.h>
#include <INWH2.h>
#include <IPL1.h>
#include <IWVN2.h>
#include <LCLS2.h>
#include <LCLSC2.h>
#include <LKS2.h>
#include <OPCC2.h>
#include <PIFN1.h>
#include <TMTYPS1.h>
#include <RIN1.h>
#include <RM2.h>
#include <ROAA2.h>
#include <ROAA3.h>
#include <ROATA2.h>
#include <ROATSA2.h>
#include <ROCN2.h>
#include <ROCNR2.h>
#include <ROCNR3.h>
#include <ROCNR4.h>
#include <ROPD1.h>
#include <SOLK2.h>
#include <SOPN2.h>
#include <SORK2.h>
#include <SOU2.h>
#include <SRL2.h>
#include <STCL2.h>
#include <THBS2.h>
#include <TPLT.h>
#include <URDS2.h>
#include <PGB2.h>
#include <PGBCL2.h>
#include <TWFA.h>
#include <TMTPST2.h>
#include <SCLB2.h>
#include <SCLBO2.h>
#include <CLNB3.h>
#include <SCLB3.h>
#include <UHBPM1.h>
#include <URBPM1.h>
#include <UNLRBPM1.h>
#include <HBPM2.h>
#include <HBPMA2.h>
#include <DCPU1.h>
#include <DCUDA1.h>
#include <DOPENCL1.h>
#include <IMD1.h>
#include <SCLBMS2.h>
#include <SCLBI2.h>
#include <ROSCD2.h>
#include <SCLSCD2.h>
#include <MAO2.h>
#include <CLMS2.h>
#include <STCFOMP2.h>
#include <OMPFJM2.h>
#include <INOMPT2.h>
#include <MNOMPT2.h>
#include <CONSTRAINTS.h>

/** @defgroup group5 String Calculation
@{  */

/** @brief Offer all available Helpers by name.
*  @details This class facilitate easy-access to all Helpers.
*/

class helperFactory
{
	public:
	/** Create Helper by name. */
	static Helper *createHelper(std::string name)
	{
		
		if(name=="IMNP1")
			return ( new IMNP1() );
		else if(name=="SN1")
			return ( new SN1() );
		else if(name=="TYPE1")
			return (new TYPE1());
		else if(name=="Cap")
			return ( new Cap() );
		else if(name=="CCCS2")
			return ( new CCCS2() );
		else if(name=="CCQN2")
			return ( new CCQN2() );
		else if(name=="CKN2")
			return ( new CKN2() );
		else if(name=="CLBN2")
			return ( new CLBN2() );
		else if(name=="CLF2")
			return ( new CLF2() );
		else if(name=="CLN2")
			return ( new CLN2() );
		else if(name=="INSTCL")
			return ( new INSTCL() );
		else if(name=="INWQM2")
			return ( new INWQM2() );	
		else if(name=="TMTYPS1")
			return ( new TMTYPS1() );		
		else if(name=="CLNB2")
			return ( new CLNB2() );
		else if(name=="CLRL2")
			return ( new CLRL2() );
		else if(name=="CLTB2")
			return ( new CLTB2() );
		else if(name=="TASKSYNC")
			return (new TASKSYNC() );
		else if(name=="PCD1")
			return (new PCD1() );	
		else if(name=="CUCC2")
			return ( new CUCC2() );
		else if(name=="DRS2")
			return ( new DRS2() );
		else if(name=="EF2")
			return (new EF2());
		else if(name=="EXTS")
			return ( new EXTS() );
		else if(name=="EXTSU")
			return ( new EXTSU() );
		else if(name=="HD2")
			return ( new HD2() );
		else if(name=="IMND1")
			return ( new IMND1() );
		else if(name=="STCL2")
			return ( new STCL2() );	
		else if(name=="IMNO1")
			return ( new IMNO1() );
		else if(name=="IMNWD1")
			return ( new IMNWD1() );
		else if(name=="IMNWO1")
			return ( new IMNWO1() );
		else if(name=="IMNWP1")
			return ( new IMNWP1() );
		else if(name=="IMPA1")
			return ( new IMPA1() );
		else if(name=="IN1")
			return ( new IN1() );
		else if(name=="INCS")
			return ( new INCS() );
		else if(name=="INCSU")
			return ( new INCSU() );
		else if(name=="INWC2")
			return ( new INWC2() );
		else if(name=="INWH2")
			return ( new INWH2() );
		else if(name=="IPL1")
			return ( new IPL1() );
		else if(name=="IWVN2")
			return ( new IWVN2() );
		else if(name=="LCLS2")
			return ( new LCLS2() );
		else if(name=="LCLSC2")
			return ( new LCLSC2() );
		else if(name=="LKS2")
			return ( new LKS2() );
		else if(name=="TMTPST2")
			return ( new TMTPST2() );
		else if(name=="OPCC2")
			return ( new OPCC2() );
		else if(name=="PIFN1")
			return (new PIFN1());
		else if(name=="RIN1")
			return (new RIN1());
		else if(name=="RM2")
			return ( new RM2() );
		else if(name=="ROAA2")
			return ( new ROAA2() );
		else if(name=="ROAA3")
			return ( new ROAA3() );	
		else if(name=="ROATA2")
			return (new ROATA2() );	
		else if(name=="ROATSA2")
			return (new ROATSA2() );
		else if(name=="ROCN2")
			return ( new ROCN2() );
		else if(name=="ROCNR2")
			return ( new ROCNR2() );
		else if(name=="ROCNR3")
			return ( new ROCNR3() );
		else if(name=="ROCNR4")
			return ( new ROCNR4() );	
		else if(name=="ROPD1")
			return ( new ROPD1() );
		else if(name=="SOLK2")
			return ( new SOLK2() );
		else if(name=="SOPN2")
			return ( new SOPN2() );
		else if(name=="SORK2")
			return ( new SORK2() );
		else if(name=="SOU2")
			return ( new SOU2() );
		else if(name=="SRL2")
			return ( new SRL2() );
		else if(name=="THBS2")
			return ( new THBS2() );
		else if(name=="TPLT")
			return ( new TPLT() );
		else if(name=="URDS2")
			return ( new URDS2() );
		else if(name=="PGB2")
			return ( new PGB2() );
		else if(name=="PGBCL2")
			return ( new PGBCL2() );
		else if(name=="TWFA")
			return ( new TWFA() );	
		else if(name=="SCLB2")
			return ( new SCLB2() );	
		else if(name=="SCLBO2")
			return ( new SCLBO2() );		
		else if(name=="CLNB3")
			return ( new CLNB3() );
		else if(name=="SCLB3")
			return ( new SCLB3() );				
		else if(name=="UHBPM1")
			return ( new UHBPM1() );
		else if(name=="URBPM1")
			return ( new URBPM1() );
		else if(name=="UNLRBPM1")
			return ( new UNLRBPM1() );		
		else if(name=="HBPM2")
			return ( new HBPM2() );
		else if(name=="HBPMA2")
			return ( new HBPMA2() );
		else if(name=="DCPU1")
			return ( new DCPU1() );	
		else if(name=="DCUDA1")
			return ( new DCUDA1() );	
		else if(name=="DOPENCL1")
			return ( new DOPENCL1() );
		else if(name=="IMD1")
			return ( new IMD1() );	
		else if(name=="SCLBMS2")	
			return ( new SCLBMS2() );
		else if(name=="SCLBI2")	
			return ( new SCLBI2() );
		else if(name=="SCLSCD2")	
			return ( new SCLSCD2() );		
		else if(name=="ROSCD2")	
			return ( new ROSCD2() );			
		else if(name=="MAO2")	
			return ( new MAO2() );
		else if(name=="CLMS2")	
			return ( new CLMS2() );		
		else if(name =="STCFOMP2")
			return ( new STCFOMP2() );
		else if(name =="OMPFJM2")
			return ( new OMPFJM2() );
		else if(name == "INOMPT2")
			return ( new INOMPT2() );
		else if(name =="MNOMPT2")
			return (new MNOMPT2());						
		else if(name == "CONSTRAINTS")
			return (new CONSTRAINTS());
		else
			return 0;
	};
};

/**	@} 
*/



#endif


