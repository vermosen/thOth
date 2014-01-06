#ifndef thoth_optimization_problem_hpp
#define thoth_optimization_problem_hpp

#include <thoth/math/optimization/method.hpp>
#include <thoth/math/optimization/costfunction.hpp>

namespace thOth {

	class Constraint;

	//! Constrained optimization problem
	/*! \warning The passed CostFunction and Constraint instances are
	stored by reference.  The user of this class must
	make sure that they are not destroyed before the
	Problem instance.
	*/
	class Problem {
	public:
		//! default constructor
		Problem(
			CostFunction& costFunction,
			Constraint& constraint,
			const Array& initialValue = Array())
			: costFunction_(costFunction), constraint_(constraint),
			currentValue_(initialValue) {}

		/*! \warning it does not reset the current minumum to any initial value
		*/
		void reset();

		//! call cost function computation and increment evaluation counter
		Real value(const Array& x);

		//! call cost values computation and increment evaluation counter
		Disposable<Array> values(const Array& x);

		//! call cost function gradient computation and increment
		//  evaluation counter
		void gradient(Array& grad_f,
			const Array& x);

		//! call cost function computation and it gradient
		Real valueAndGradient(Array& grad_f,
			const Array& x);

		//! Constraint
		Constraint& constraint() const { return constraint_; }

		//! Cost function
		CostFunction& costFunction() const { return costFunction_; }

		void setCurrentValue(const Array& currentValue) {
			currentValue_ = currentValue;
		}

		//! current value of the local minimum
		const Array& currentValue() const { return currentValue_; }

		void setFunctionValue(Real functionValue) {
			functionValue_ = functionValue;
		}

		//! value of cost function
		Real functionValue() const { return functionValue_; }

		void setGradientNormValue(Real squaredNorm) {
			squaredNorm_ = squaredNorm;
		}
		//! value of cost function gradient norm
		Real gradientNormValue() const { return squaredNorm_; }

		//! number of evaluation of cost function
		Integer functionEvaluation() const { return functionEvaluation_; }

		//! number of evaluation of cost function gradient
		Integer gradientEvaluation() const { return gradientEvaluation_; }

	protected:
		//! Unconstrained cost function
		CostFunction& costFunction_;
		//! Constraint
		Constraint& constraint_;
		//! current value of the local minimum
		Array currentValue_;
		//! function and gradient norm values at the curentValue_ (i.e. the last step)
		Real functionValue_, squaredNorm_;
		//! number of evaluation of cost function and its gradient
		Integer functionEvaluation_, gradientEvaluation_;
	};

	// inline definitions
	inline Real Problem::value(const Array& x) {
		++functionEvaluation_;
		return costFunction_.value(x);
	}

	inline Disposable<Array> Problem::values(const Array& x) {
		++functionEvaluation_;
		return costFunction_.values(x);
	}

	inline void Problem::gradient(Array& grad_f,
		const Array& x) {
		++gradientEvaluation_;
		costFunction_.gradient(grad_f, x);
	}

	inline Real Problem::valueAndGradient(Array& grad_f,
		const Array& x) {
		++functionEvaluation_;
		++gradientEvaluation_;
		return costFunction_.valueAndGradient(grad_f, x);
	}

	inline void Problem::reset() {
		functionEvaluation_ = gradientEvaluation_ = 0;
		functionValue_ = squaredNorm_ = Null<Real>();
	}

}

#endif
