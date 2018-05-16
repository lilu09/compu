


#ifndef CONSTRAINTS_H_
#define CONSTRAINTS_H_

#include <vector>
#include <string>
#include <algorithm>
#include <compose.h>
#include <static_constraint_evaluator.hpp>
#include <methods.h>


class Constraint
{
	public:
		Constraint():constraint_satisfied(false){}
		Constraint(std::string& a_constraint): Constraint() { constraint=std::move(a_constraint); c_compatibility_update(); }
		virtual bool eval_constraint()=0; 
		virtual void print_me()=0; 

	protected:
		std::string constraint;
		bool constraint_satisfied;
		void c_compatibility_update() { 
			std::replace(constraint.begin(), constraint.end(), '{', '<');
			std::replace(constraint.begin(), constraint.end(), '}', '>');
		}
};



class Static_Constraint : public Constraint
{
	public:
		using Constraint::Constraint;
		bool eval_constraint() override final {
			string lib_name, lib_query_prepare_cmd;
			//if is_installed called, generate the struct represent the library name
			if(constraint.find("is_installed") != std::string::npos){
				//get string between "," and ">"
				auto first=constraint.find(",");
				auto last=constraint.find(">");
				lib_name=constraint.substr(first+1, last-first-1);
				assertx(lib_name!="", "You should get a nonempty string here, but you don't");
				lib_query_prepare_cmd="XDPL_PREPAPRE_SW_QUERY("+lib_name+");";
			}
			constraint_satisfied=static_constraint_evaluator(constraint, lib_query_prepare_cmd);
			return constraint_satisfied;
		}
		void print_me() override final { 
			std::cout<<"static constraint: "<<constraint<<", satisfied: "<<std::boolalpha<<constraint_satisfied<<std::endl;
		}
};


class Dynamic_Constraint : public Constraint
{
	public:
		using Constraint::Constraint;
		bool eval_constraint() override final{ return false; } //intentionally empty, dynamic constraints can not be evaluated by composition tool
		void print_me() override final { 
			std::cout<<"dynamic constraint: "<<constraint<<std::endl;
		}
};


class Constraints
{
	public:
		Constraints():constraints_satisfied(false){}
		//seems not needed, weird, find out later
		//~Constraints(){ compose( constraints, delete constraints[_index] ; );  }
		void add(Constraint * const  a_constraint) { constraints.push_back(a_constraint); }
		bool eval_constraints(){
			compose( constraints, if( !constraints[_index]->eval_constraint() ) {constraints_satisfied=false; constraints[_index]->print_me(); return false;} constraints[_index]->print_me(); );
			//print_me();
			constraints_satisfied=true;
			return true;
		}
		void print_me(){ 
			compose( constraints, constraints[_index]->print_me(); ); 
		}

	private:
		std::vector<Constraint *> constraints;
		bool constraints_satisfied;
};





#endif
