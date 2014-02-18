#ifndef thoth_optimization_problem_hpp
#define thoth_optimization_problem_hpp

#include <thoth/math/optimization/method.hpp>
#include <thoth/math/optimization/costfunction.hpp>
#include <thOth/types.hpp>

#include <boost/numeric/ublas/vector.hpp>

namespace thOth {

	class Constraint;
	class CostFunction;

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
			const boost::numeric::ublas::vector<double>& initialValue = Array())
			: costFunction_(costFunction), constraint_(constraint),
			currentValue_(initialValue) {}

		/*! \warning it does not reset the current minumum to any initial value
		*/
		void reset();

		//! call cost function computation and increment evaluation counter
		real value(const boost::numeric::ublas::vector<double>& x);

		//! call cost values computation and increment evaluation counter
		Disposable<Array> values(const boost::numeric::ublas::vector<double>& x);

		//! call cost function gradient computation and increment
		//  evaluation counter
		void gradient(boost::numeric::ublas::vector<double>& grad_f,
			const boost::numeric::ublas::vector<double>& x);

		//! call cost function computation and it gradient
		real valueAndGradient(boost::numeric::ublas::vector<double>& grad_f,
			const boost::numeric::ublas::vector<double>& x);

		//! Constraint
		Constraint& constraint() const { return constraint_; }

		//! Cost function
		CostFunction& costFunction() const { return costFunction_; }

		void setCurrentValue(const boost::numeric::ublas::vector<double>& currentValue) {
			currentValue_ = currentValue;
		}

		//! current value of the local minimum
		const boost::numeric::ublas::vector<double>& currentValue() const { return currentValue_; }

		void setFunctionValue(real functionValue) {
			functionValue_ = functionValue;
		}

		//! value of cost function
		real functionValue() const { return functionValue_; }

		void setGradientNormValue(real squaredNorm) {
			squaredNorm_ = squaredNorm;
		}
		//! value of cost function gradient norm
		real gradientNormValue() const { return squaredNorm_; }

		//! number of evaluation of cost function
		int functionEvaluation() const { return functionEvaluation_; }

		//! number of evaluation of cost function gradient
		int gradientEvaluation() const { return gradientEvaluation_; }

	protected:
		//! Unconstrained cost function
		CostFunction& costFunction_;
		//! Constraint
		Constraint& constraint_;
		//! current value of the local minimum
		boost::numeric::ublas::vector<double> currentValue_;
		//! function and gradient norm values at the curentValue_ (i.e. the last step)
		real functionValue_, squaredNorm_;
		//! number of evaluation of cost function and its gradient
		int functionEvaluation_, gradientEvaluation_;
	};

	// inline definitions
	inline real Problem::value(const boost::numeric::ublas::vector<double>& x) {
		++functionEvaluation_;
		return costFunction_.value(x);
	}

	inline Disposable<Array> Problem::values(const boost::numeric::ublas::vector<double>& x) {
		++functionEvaluation_;
		return costFunction_.values(x);
	}

	inline void Problem::gradient(boost::numeric::ublas::vector<double>& grad_f,
		const boost::numeric::ublas::vector<double>& x) {
		++gradientEvaluation_;
		costFunction_.gradient(grad_f, x);
	}

	inline real Problem::valueAndGradient(boost::numeric::ublas::vector<double>& grad_f,
		const boost::numeric::ublas::vector<double>& x) {
		++functionEvaluation_;
		++gradientEvaluation_;
		return costFunction_.valueAndGradient(grad_f, x);
	}

	inline void Problem::reset() {
		functionEvaluation_ = gradientEvaluation_ = 0;
		functionValue_ = squaredNorm_ = Null<real>();
	}

}

#endif
