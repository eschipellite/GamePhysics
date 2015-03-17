//=============================================================================
#ifndef GENERATOR_H
#define GENERATOR_H
//=============================================================================
//                              Force Types
//
// Written by Evan Schipellite
//
// Enum for Generators
//=============================================================================
enum GeneratorType
{
	GENERATOR,
	FORCE_GENERATOR,
	OBJECT_FORCE_GENERATOR,
	GRAVITY_GENERATOR
};
//=============================================================================

//=============================================================================
//                              Generator
//
// Written by Evan Schipellite
//
// Simple Generator structure
//=============================================================================
class Generator
{
protected:
	GeneratorType m_GeneratorType;

public:
	Generator();
	~Generator();

	GeneratorType GetGeneratorType();
};
//=============================================================================
#endif // GENERATOR_H

