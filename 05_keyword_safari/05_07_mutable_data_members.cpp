
class ComplexShape {
	mutable bool volumeCalculated = false;
	mutable double volume;

	double calculateVolume() const { /* ... */ }

  public:
	ComplexShape( /* ... */ ) { /* ... */ }

	// Semantically, getVolume does not
	// modify the state of ComplexShape
	double getVolume() const {
		if(!volumeCalculated) {
			volume = calculateVolume();
			volumeCalculated = true;
		}
		return volume;
	}
};
