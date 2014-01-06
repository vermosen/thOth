#include "thOth/time/occurence.h"
#include "thOth/pattern/acyclicVisitor.h"
#include "thOth/pattern/visitor.h"

namespace thOth {

	bool occurence::hasOccurred(
		const dateTime& d,
		const bool& includeRefDateEvent) const {

		dateTime refDate = d;

		if (includeRefDateEvent)
			return date() < refDate;
		else
			return date() <= refDate;
	
	}

	void occurence::accept(acyclicVisitor& v) {
		visitor<occurence>* v1 = dynamic_cast<visitor<occurence>*>(&v);
		
		if (v1 != 0)
			v1->visit(*this);
		else
			return;
		
		// throw exception
			//QL_FAIL("not an occurence visitor");
	}

}
