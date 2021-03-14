#pragma once
#include "Platform.h"
#include <typeinfo>
#include <string>
#include <functional>
#include "Typedef.h"

namespace dyno {
	class Base;

	enum EFieldType
	{
		In,
		Out,
		Param,
		Current,
		Next
	};

/*!
*	\class	Variable
*	\brief	Interface for all variables.
*/
class FieldBase
{
	using CallBackFunc = std::function<void()>;
public:
	FieldBase() : m_name("default"), m_description("") {};
	FieldBase(std::string name, std::string description, EFieldType type = EFieldType::Param, Base* parent = nullptr);
	virtual ~FieldBase() {};

	virtual size_t getElementCount() { return 0; }
	virtual const std::string getTemplateName() { return std::string(""); }
	virtual const std::string getClassName() { return std::string("Field"); }

	std::string	getObjectName() { return m_name; }
	std::string	getDescription() { return m_description; }
	virtual DeviceType getDeviceType() { return DeviceType::UNDEFINED; }

	void setObjectName(std::string name) { m_name = name; }
	void setDescription(std::string description) { m_description = description; }

	void setParent(Base* owner);
	Base* getParent();

	bool isDerived();
	bool isAutoDestroyable();

	void setAutoDestroy(bool autoDestroy);
	void setDerived(bool derived);

	std::vector<FieldBase*>& getSinkFields() { return m_field_sink; }

	bool isModified();
	void tagModified(bool modifed);

	bool isOptional();
	void tagOptional(bool optional);

	inline float getMin() { return m_min; }
	inline void setMin(float min_val) { m_min = min_val; }

	inline float getMax() { return m_max; }
	inline void setMax(float max_val) { m_max = max_val; }

	EFieldType getFieldType();


	bool connectField(FieldBase* dst);

	FieldBase* getTopField();

	virtual bool isEmpty() = 0;
	virtual void update();

	void setCallBackFunc(CallBackFunc func) { callbackFunc = func; }
protected:
	void setSource(FieldBase* source);
	FieldBase* getSource();

	void addSink(FieldBase* f);
	void removeSink(FieldBase* f);

	EFieldType m_fType = EFieldType::Param;

private:
	std::string m_name;
	std::string m_description;

	bool m_optional = false;

	bool m_autoDestroyable = true;
	bool m_derived = false;
	FieldBase* m_source = nullptr;
	Base* m_owner = nullptr;

	float m_min = -FLT_MAX;
	float m_max = FLT_MAX;

	bool m_modified = false;

	std::vector<FieldBase*> m_field_sink;
	CallBackFunc callbackFunc;
};

#define DEFINE_DERIVED_FUNC(DerivedField,Data)						\
std::shared_ptr<Data>& getReference()								\
{																	\
	FieldBase* topField = this->getTopField();							\
	DerivedField* derived = dynamic_cast<DerivedField*>(topField);	\
	return derived->m_data;											\
}																	\
\
bool isEmpty() override {											\
return this->getReference() == nullptr;								\
}																	\
\
bool connect(DerivedField* dst)						\
{																	\
	this->connectField(dst);										\
	this->update();													\
	return true;													\
}																	\
Data& getValue() { return *(getReference()); }					\
private:															\
	std::shared_ptr<Data> m_data = nullptr;							\
public:

}