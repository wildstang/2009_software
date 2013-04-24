#ifndef SIMLIB_H_
#define SIMLIB_H_

/**
 * Class of static methods for common operations.
 */ 
class SimLib
{
public:
	static float limitOutput(float f);
	static float signSquare(float f);

private:
	// Ensure this class can't be instantiated.
	SimLib() {}
};

#endif // SIMLIB_H_
