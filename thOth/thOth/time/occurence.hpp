#ifndef thoth_occurence_hpp
#define thoth_occurence_hpp

#include <thOth/pattern/observable.hpp>
#include <thOth/time/dateTime.hpp>

namespace thOth {

	class acyclicVisitor;


	// not sure about the observable inheritance...
	class occurence : public observable	{

	public:
		virtual ~occurence() {}
		
		// Occurence interface
		// returns the date at which the event occured
		virtual dateTime date() const = 0;

		// returns true if an event has already occurred at a given date
		// If includeRefDate is true, then an event has not occurred if its
		// date is the same as the refDate.
		virtual bool hasOccurred(
			const dateTime& refDate = dateTime(),
			const bool& includeRefDateEvent = true) const;
		
		// name Visitability
		virtual void accept(acyclicVisitor&);

	};

#ifdef _DEBUG
	namespace debug {

		// create basic occurence implementation for test purpose
		class simpleOccurence : public occurence {
		
		public:
		
			simpleOccurence(const dateTime& date) : date_(date) {}
			dateTime date() const { return date_; }
		
		private:
			
			dateTime date_;
		
		};
	}

#endif

}

#endif

