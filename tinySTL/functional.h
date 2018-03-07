#ifndef _SZ_FUNCTIONAL_H_
#define _SZ_FUNCTIONAL_H_
namespace sz {

#define _func_obj_2op(name, calc, _type) template<class T=void> \
	struct name { \
		typedef _type	result_type; \
		typedef T		first_argument_type; \
		typedef T		second_argument_type; \
		result_type operator()(const first_argument_type& lhs, const second_argument_type& rhs) const { \
			return lhs calc rhs; \
		} \
	};

#define _func_obj_1op(name, calc, _type) template<class T=void> \
	struct name { \
		typedef _type	result_type; \
		typedef T		argument_type; \
		result_type operator()(const argument_type& arg) const { \
			return calc rhs; \
		} \
	};

#define _func_calc_2op(name, calc_) _func_obj_2op(name, calc_, T)
#define _func_calc_1op(name, calc_) _func_obj_1op(name, calc_, T)
#define _func_judge_2op(name, judge_) _func_obj_2op(name, judge_, bool)
#define _func_logic_2op(name, logic_) _func_obj_2op(name, logic_, bool)
#define _func_logic_1op(name, logic_) _func_obj_1op(name, logic_, bool)

	_func_calc_2op(plus, +);
	_func_calc_2op(minus, -);
	_func_calc_2op(multiplies, *);
	_func_calc_2op(divides, / );
	_func_calc_2op(modulus, %);
	_func_calc_1op(negate, -);

	_func_judge_2op(equal_to, == );
	_func_judge_2op(not_equal_to, != );
	_func_judge_2op(greater, > );
	_func_judge_2op(less, < );
	_func_judge_2op(greater_equal, >= );
	_func_judge_2op(less_equal, <= );

	_func_logic_2op(logical_and, &&);
	_func_logic_2op(logical_or, || );
	_func_logic_1op(logical_not, !);

	_func_calc_2op(bit_and, &);
	_func_calc_2op(bit_or, | );
	_func_calc_2op(bit_xor, ^);
	_func_calc_1op(bit_not, ~);

	template<class T = void> 
	struct logical_true_2op {
		
		typedef bool	result_type; 
		typedef T		first_argument_type; 
		typedef T		second_argument_type; 
		result_type operator()(const first_argument_type& lhs, const second_argument_type& rhs) const {
			return true;
		} 
	};
	template<class T = void> 
	struct logical_true_1op {
		typedef bool	result_type; 
		typedef T		argument_type; 
		result_type operator()(const argument_type& arg) const {
			return true;
		} 
	};

}

#endif // !_SZ_FUNCTIONAL_H_
