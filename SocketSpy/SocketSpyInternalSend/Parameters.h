#pragma once

#include <vector>

#include "MessageView.h"

namespace SocketSpy
{

#define MAKE_VIEW_PARAMETER_GET_PRIMITIVE(Type, PublicName, StringName)			\
class PublicName : public MessageView											\
{																				\
public:																			\
	PublicName(HttpRequest& httpRequest)										\
		: MessageView{ httpRequest }											\
	{																			\
		Mutator().MapToQueryParameter(m_value, StringName);						\
	}																			\
																				\
	const Type Value() const													\
	{																			\
		return m_value;															\
	}																			\
																				\
	void Value(Type newValue)													\
	{																			\
		Mutator().WritebackQueryParameter(m_value, newValue, StringName);		\
	}																			\
																				\
private:																		\
		Type m_value;															\
};

#define MAKE_VIEW_PARAMETER_POST_PRIMITIVE(Type, PublicName, StringName)		\
class PublicName : public MessageView											\
{																				\
public:																			\
	PublicName(HttpRequest& httpRequest)										\
		: MessageView{ httpRequest }											\
	{																			\
		Mutator().MapToContentParameter(m_value, StringName);					\
	}																			\
																				\
	const Type Value() const													\
	{																			\
		return m_value;															\
	}																			\
																				\
	void Value(Type newValue)													\
	{																			\
		Mutator().WritebackContent(m_value, newValue, StringName);				\
	}																			\
																				\
private:																		\
		Type m_value;															\
};

#define MAKE_VIEW_PARAMETER_GET_COMPLEX(PublicName, StringName)					\
class PublicName : public MessageView											\
{																				\
public:																			\
	PublicName(HttpRequest& httpRequest)										\
		: MessageView{ httpRequest }											\
	{																			\
		Mutator().MapToQueryParameter(m_value, StringName);						\
	}																			\
																				\
	const std::vector<char>& Value() const										\
	{																			\
		return m_value;															\
	}																			\
																				\
	void Value(std::vector<char>& newValue)										\
	{																			\
		Mutator().WritebackQueryParameter(m_value, newValue, StringName);		\
	}																			\
																				\
private:																		\
		std::vector<char> m_value;												\
};

#define MAKE_VIEW_PARAMETER_POST_COMPLEX(PublicName, StringName)				\
class PublicName : public MessageView											\
{																				\
public:																			\
	PublicName(HttpRequest& httpRequest)										\
		: MessageView{ httpRequest }											\
	{																			\
		Mutator().MapToContentParameter(m_value, StringName);					\
	}																			\
																				\
	const std::vector<char>& Value() const										\
	{																			\
		return m_value;															\
	}																			\
																				\
	void Value(std::vector<char>& newValue)										\
	{																			\
		Mutator().WritebackContent(m_value, newValue, StringName);				\
	}																			\
																				\
private:																		\
		std::vector<char> m_value;												\
};

#define APPEND_VALUE(ParamName) ParamName ## Value
#define PREPEND_MEMBER(ParamName) m_ ## ParamName

#define MAKE_VIEW1(PublicName, Param1)											\
class PublicName																\
{																				\
public:																			\
	PublicName(HttpRequest& httpRequest)										\
		: PREPEND_MEMBER(Param1) { httpRequest }								\
	{																			\
	}																			\
																				\
	Param1& APPEND_VALUE(Param1)()												\
	{																			\
		return PREPEND_MEMBER(Param1);											\
	}																			\
																				\
private:																		\
	Param1 PREPEND_MEMBER(Param1);												\
};

#define MAKE_VIEW2(PublicName, Param1, Param2)									\
class PublicName																\
{																				\
public:																			\
	PublicName(HttpRequest& httpRequest)										\
		: PREPEND_MEMBER(Param1) { httpRequest },								\
		PREPEND_MEMBER(Param2) { httpRequest }									\
	{																			\
	}																			\
																				\
	Param1& APPEND_VALUE(Param1)()												\
	{																			\
		return PREPEND_MEMBER(Param1);											\
	}																			\
																				\
	Param2& APPEND_VALUE(Param2)()												\
	{																			\
		return PREPEND_MEMBER(Param2);											\
	}																			\
																				\
private:																		\
	Param1 PREPEND_MEMBER(Param1);												\
	Param2 PREPEND_MEMBER(Param2);												\
};

#define MAKE_VIEW3(PublicName, Param1, Param2, Param3)							\
class PublicName																\
{																				\
public:																			\
	PublicName(HttpRequest& httpRequest)										\
		: PREPEND_MEMBER(Param1) { httpRequest },								\
		PREPEND_MEMBER(Param2) { httpRequest },									\
		PREPEND_MEMBER(Param3) { httpRequest }									\
	{																			\
	}																			\
																				\
	Param1& APPEND_VALUE(Param1)()												\
	{																			\
		return PREPEND_MEMBER(Param1);											\
	}																			\
																				\
	Param2& APPEND_VALUE(Param2)()												\
	{																			\
		return PREPEND_MEMBER(Param2);											\
	}																			\
																				\
	Param3& APPEND_VALUE(Param3)()												\
	{																			\
		return PREPEND_MEMBER(Param3);											\
	}																			\
																				\
private:																		\
	Param1 PREPEND_MEMBER(Param1);												\
	Param2 PREPEND_MEMBER(Param2);												\
	Param3 PREPEND_MEMBER(Param3);												\
};

#define MAKE_VIEW4(PublicName, Param1, Param2, Param3, Param4)					\
class PublicName																\
{																				\
public:																			\
	PublicName(HttpRequest& httpRequest)										\
		: PREPEND_MEMBER(Param1) { httpRequest },								\
		PREPEND_MEMBER(Param2) { httpRequest },									\
		PREPEND_MEMBER(Param3) { httpRequest },									\
		PREPEND_MEMBER(Param4) { httpRequest }									\
	{																			\
	}																			\
																				\
	Param1& APPEND_VALUE(Param1)()												\
	{																			\
		return PREPEND_MEMBER(Param1);											\
	}																			\
																				\
	Param2& APPEND_VALUE(Param2)()												\
	{																			\
		return PREPEND_MEMBER(Param2);											\
	}																			\
																				\
	Param3& APPEND_VALUE(Param3)()												\
	{																			\
		return PREPEND_MEMBER(Param3);											\
	}																			\
																				\
	Param4& APPEND_VALUE(Param4)()												\
	{																			\
		return PREPEND_MEMBER(Param4);											\
	}																			\
																				\
private:																		\
	Param1 PREPEND_MEMBER(Param1);												\
	Param2 PREPEND_MEMBER(Param2);												\
	Param3 PREPEND_MEMBER(Param3);												\
	Param4 PREPEND_MEMBER(Param4);												\
};

#define MAKE_VIEW5(PublicName, Param1, Param2, Param3, Param4, Param5)			\
class PublicName																\
{																				\
public:																			\
	PublicName(HttpRequest& httpRequest)										\
		: PREPEND_MEMBER(Param1) { httpRequest },								\
		PREPEND_MEMBER(Param2) { httpRequest },									\
		PREPEND_MEMBER(Param3) { httpRequest },									\
		PREPEND_MEMBER(Param4) { httpRequest },									\
		PREPEND_MEMBER(Param5) { httpRequest }									\
	{																			\
	}																			\
																				\
	Param1& APPEND_VALUE(Param1)()												\
	{																			\
		return PREPEND_MEMBER(Param1);											\
	}																			\
																				\
	Param2& APPEND_VALUE(Param2)()												\
	{																			\
		return PREPEND_MEMBER(Param2);											\
	}																			\
																				\
	Param3& APPEND_VALUE(Param3)()												\
	{																			\
		return PREPEND_MEMBER(Param3);											\
	}																			\
																				\
	Param4& APPEND_VALUE(Param4)()												\
	{																			\
		return PREPEND_MEMBER(Param4);											\
	}																			\
																				\
	Param5& APPEND_VALUE(Param5)()												\
	{																			\
		return PREPEND_MEMBER(Param5);											\
	}																			\
																				\
private:																		\
	Param1 PREPEND_MEMBER(Param1);												\
	Param2 PREPEND_MEMBER(Param2);												\
	Param3 PREPEND_MEMBER(Param3);												\
	Param4 PREPEND_MEMBER(Param4);												\
	Param5 PREPEND_MEMBER(Param5);												\
};

#define MAKE_VIEW6(PublicName, Param1, Param2, Param3, Param4, Param5,			\
	Param6)																		\
class PublicName																\
{																				\
public:																			\
	PublicName(HttpRequest& httpRequest)										\
		: PREPEND_MEMBER(Param1) { httpRequest },								\
		PREPEND_MEMBER(Param2) { httpRequest },									\
		PREPEND_MEMBER(Param3) { httpRequest },									\
		PREPEND_MEMBER(Param4) { httpRequest },									\
		PREPEND_MEMBER(Param5) { httpRequest },									\
		PREPEND_MEMBER(Param6) { httpRequest }									\
	{																			\
	}																			\
																				\
	Param1& APPEND_VALUE(Param1)()												\
	{																			\
		return PREPEND_MEMBER(Param1);											\
	}																			\
																				\
	Param2& APPEND_VALUE(Param2)()												\
	{																			\
		return PREPEND_MEMBER(Param2);											\
	}																			\
																				\
	Param3& APPEND_VALUE(Param3)()												\
	{																			\
		return PREPEND_MEMBER(Param3);											\
	}																			\
																				\
	Param4& APPEND_VALUE(Param4)()												\
	{																			\
		return PREPEND_MEMBER(Param4);											\
	}																			\
																				\
	Param5& APPEND_VALUE(Param5)()												\
	{																			\
		return PREPEND_MEMBER(Param5);											\
	}																			\
																				\
	Param6& APPEND_VALUE(Param6)()												\
	{																			\
		return PREPEND_MEMBER(Param6);											\
	}																			\
																				\
private:																		\
	Param1 PREPEND_MEMBER(Param1);												\
	Param2 PREPEND_MEMBER(Param2);												\
	Param3 PREPEND_MEMBER(Param3);												\
	Param4 PREPEND_MEMBER(Param4);												\
	Param5 PREPEND_MEMBER(Param5);												\
	Param6 PREPEND_MEMBER(Param6);												\
};

#define MAKE_VIEW7(PublicName, Param1, Param2, Param3, Param4, Param5,			\
	Param6, Param7)																\
class PublicName																\
{																				\
public:																			\
	PublicName(HttpRequest& httpRequest)										\
		: PREPEND_MEMBER(Param1) { httpRequest },								\
		PREPEND_MEMBER(Param2) { httpRequest },									\
		PREPEND_MEMBER(Param3) { httpRequest },									\
		PREPEND_MEMBER(Param4) { httpRequest },									\
		PREPEND_MEMBER(Param5) { httpRequest },									\
		PREPEND_MEMBER(Param6) { httpRequest },									\
		PREPEND_MEMBER(Param7) { httpRequest }									\
	{																			\
	}																			\
																				\
	Param1& APPEND_VALUE(Param1)()												\
	{																			\
		return PREPEND_MEMBER(Param1);											\
	}																			\
																				\
	Param2& APPEND_VALUE(Param2)()												\
	{																			\
		return PREPEND_MEMBER(Param2);											\
	}																			\
																				\
	Param3& APPEND_VALUE(Param3)()												\
	{																			\
		return PREPEND_MEMBER(Param3);											\
	}																			\
																				\
	Param4& APPEND_VALUE(Param4)()												\
	{																			\
		return PREPEND_MEMBER(Param4);											\
	}																			\
																				\
	Param5& APPEND_VALUE(Param5)()												\
	{																			\
		return PREPEND_MEMBER(Param5);											\
	}																			\
																				\
	Param6& APPEND_VALUE(Param6)()												\
	{																			\
		return PREPEND_MEMBER(Param6);											\
	}																			\
																				\
	Param7& APPEND_VALUE(Param7)()												\
	{																			\
		return PREPEND_MEMBER(Param7);											\
	}																			\
																				\
private:																		\
	Param1 PREPEND_MEMBER(Param1);												\
	Param2 PREPEND_MEMBER(Param2);												\
	Param3 PREPEND_MEMBER(Param3);												\
	Param4 PREPEND_MEMBER(Param4);												\
	Param5 PREPEND_MEMBER(Param5);												\
	Param6 PREPEND_MEMBER(Param6);												\
	Param7 PREPEND_MEMBER(Param7);												\
};

#define MAKE_VIEW8(PublicName, Param1, Param2, Param3, Param4, Param5,			\
	Param6, Param7, Param8)														\
class PublicName																\
{																				\
public:																			\
	PublicName(HttpRequest& httpRequest)										\
		: PREPEND_MEMBER(Param1) { httpRequest },								\
		PREPEND_MEMBER(Param2) { httpRequest },									\
		PREPEND_MEMBER(Param3) { httpRequest },									\
		PREPEND_MEMBER(Param4) { httpRequest },									\
		PREPEND_MEMBER(Param5) { httpRequest },									\
		PREPEND_MEMBER(Param6) { httpRequest },									\
		PREPEND_MEMBER(Param7) { httpRequest },									\
		PREPEND_MEMBER(Param8) { httpRequest }									\
	{																			\
	}																			\
																				\
	Param1& APPEND_VALUE(Param1)()												\
	{																			\
		return PREPEND_MEMBER(Param1);											\
	}																			\
																				\
	Param2& APPEND_VALUE(Param2)()												\
	{																			\
		return PREPEND_MEMBER(Param2);											\
	}																			\
																				\
	Param3& APPEND_VALUE(Param3)()												\
	{																			\
		return PREPEND_MEMBER(Param3);											\
	}																			\
																				\
	Param4& APPEND_VALUE(Param4)()												\
	{																			\
		return PREPEND_MEMBER(Param4);											\
	}																			\
																				\
	Param5& APPEND_VALUE(Param5)()												\
	{																			\
		return PREPEND_MEMBER(Param5);											\
	}																			\
																				\
	Param6& APPEND_VALUE(Param6)()												\
	{																			\
		return PREPEND_MEMBER(Param6);											\
	}																			\
																				\
	Param7& APPEND_VALUE(Param7)()												\
	{																			\
		return PREPEND_MEMBER(Param7);											\
	}																			\
																				\
	Param8& APPEND_VALUE(Param8)()												\
	{																			\
		return PREPEND_MEMBER(Param8);											\
	}																			\
																				\
private:																		\
	Param1 PREPEND_MEMBER(Param1);												\
	Param2 PREPEND_MEMBER(Param2);												\
	Param3 PREPEND_MEMBER(Param3);												\
	Param4 PREPEND_MEMBER(Param4);												\
	Param5 PREPEND_MEMBER(Param5);												\
	Param6 PREPEND_MEMBER(Param6);												\
	Param7 PREPEND_MEMBER(Param7);												\
	Param8 PREPEND_MEMBER(Param8);												\
};

#define MAKE_VIEW9(PublicName, Param1, Param2, Param3, Param4, Param5,			\
	Param6, Param7, Param8, Param9)												\
class PublicName																\
{																				\
public:																			\
	PublicName(HttpRequest& httpRequest)										\
		: PREPEND_MEMBER(Param1) { httpRequest },								\
		PREPEND_MEMBER(Param2) { httpRequest },									\
		PREPEND_MEMBER(Param3) { httpRequest },									\
		PREPEND_MEMBER(Param4) { httpRequest },									\
		PREPEND_MEMBER(Param5) { httpRequest },									\
		PREPEND_MEMBER(Param6) { httpRequest },									\
		PREPEND_MEMBER(Param7) { httpRequest },									\
		PREPEND_MEMBER(Param8) { httpRequest },									\
		PREPEND_MEMBER(Param9) { httpRequest }									\
	{																			\
	}																			\
																				\
	Param1& APPEND_VALUE(Param1)()												\
	{																			\
		return PREPEND_MEMBER(Param1);											\
	}																			\
																				\
	Param2& APPEND_VALUE(Param2)()												\
	{																			\
		return PREPEND_MEMBER(Param2);											\
	}																			\
																				\
	Param3& APPEND_VALUE(Param3)()												\
	{																			\
		return PREPEND_MEMBER(Param3);											\
	}																			\
																				\
	Param4& APPEND_VALUE(Param4)()												\
	{																			\
		return PREPEND_MEMBER(Param4);											\
	}																			\
																				\
	Param5& APPEND_VALUE(Param5)()												\
	{																			\
		return PREPEND_MEMBER(Param5);											\
	}																			\
																				\
	Param6& APPEND_VALUE(Param6)()												\
	{																			\
		return PREPEND_MEMBER(Param6);											\
	}																			\
																				\
	Param7& APPEND_VALUE(Param7)()												\
	{																			\
		return PREPEND_MEMBER(Param7);											\
	}																			\
																				\
	Param8& APPEND_VALUE(Param8)()												\
	{																			\
		return PREPEND_MEMBER(Param8);											\
	}																			\
																				\
	Param9& APPEND_VALUE(Param9)()												\
	{																			\
		return PREPEND_MEMBER(Param9);											\
	}																			\
																				\
private:																		\
	Param1 PREPEND_MEMBER(Param1);												\
	Param2 PREPEND_MEMBER(Param2);												\
	Param3 PREPEND_MEMBER(Param3);												\
	Param4 PREPEND_MEMBER(Param4);												\
	Param5 PREPEND_MEMBER(Param5);												\
	Param6 PREPEND_MEMBER(Param6);												\
	Param7 PREPEND_MEMBER(Param7);												\
	Param8 PREPEND_MEMBER(Param8);												\
	Param9 PREPEND_MEMBER(Param9);												\
};

#define MAKE_VIEW10(PublicName, Param1, Param2, Param3, Param4, Param5,			\
	Param6, Param7, Param8, Param9, Param10)									\
class PublicName																\
{																				\
public:																			\
	PublicName(HttpRequest& httpRequest)										\
		: PREPEND_MEMBER(Param1) { httpRequest },								\
		PREPEND_MEMBER(Param2) { httpRequest },									\
		PREPEND_MEMBER(Param3) { httpRequest },									\
		PREPEND_MEMBER(Param4) { httpRequest },									\
		PREPEND_MEMBER(Param5) { httpRequest },									\
		PREPEND_MEMBER(Param6) { httpRequest },									\
		PREPEND_MEMBER(Param7) { httpRequest },									\
		PREPEND_MEMBER(Param8) { httpRequest },									\
		PREPEND_MEMBER(Param9) { httpRequest },									\
		PREPEND_MEMBER(Param10) { httpRequest }									\
	{																			\
	}																			\
																				\
	Param1& APPEND_VALUE(Param1)()												\
	{																			\
		return PREPEND_MEMBER(Param1);											\
	}																			\
																				\
	Param2& APPEND_VALUE(Param2)()												\
	{																			\
		return PREPEND_MEMBER(Param2);											\
	}																			\
																				\
	Param3& APPEND_VALUE(Param3)()												\
	{																			\
		return PREPEND_MEMBER(Param3);											\
	}																			\
																				\
	Param4& APPEND_VALUE(Param4)()												\
	{																			\
		return PREPEND_MEMBER(Param4);											\
	}																			\
																				\
	Param5& APPEND_VALUE(Param5)()												\
	{																			\
		return PREPEND_MEMBER(Param5);											\
	}																			\
																				\
	Param6& APPEND_VALUE(Param6)()												\
	{																			\
		return PREPEND_MEMBER(Param6);											\
	}																			\
																				\
	Param7& APPEND_VALUE(Param7)()												\
	{																			\
		return PREPEND_MEMBER(Param7);											\
	}																			\
																				\
	Param8& APPEND_VALUE(Param8)()												\
	{																			\
		return PREPEND_MEMBER(Param8);											\
	}																			\
																				\
	Param9& APPEND_VALUE(Param9)()												\
	{																			\
		return PREPEND_MEMBER(Param9);											\
	}																			\
																				\
	Param10& APPEND_VALUE(Param10)()											\
	{																			\
		return PREPEND_MEMBER(Param10);											\
	}																			\
																				\
private:																		\
	Param1 PREPEND_MEMBER(Param1);												\
	Param2 PREPEND_MEMBER(Param2);												\
	Param3 PREPEND_MEMBER(Param3);												\
	Param4 PREPEND_MEMBER(Param4);												\
	Param5 PREPEND_MEMBER(Param5);												\
	Param6 PREPEND_MEMBER(Param6);												\
	Param7 PREPEND_MEMBER(Param7);												\
	Param8 PREPEND_MEMBER(Param8);												\
	Param9 PREPEND_MEMBER(Param9);												\
	Param10 PREPEND_MEMBER(Param10);											\
};

#define MAKE_VIEW11(PublicName, Param1, Param2, Param3, Param4, Param5,			\
	Param6, Param7, Param8, Param9, Param10, Param11)							\
class PublicName																\
{																				\
public:																			\
	PublicName(HttpRequest& httpRequest)										\
		: PREPEND_MEMBER(Param1) { httpRequest },								\
		PREPEND_MEMBER(Param2) { httpRequest },									\
		PREPEND_MEMBER(Param3) { httpRequest },									\
		PREPEND_MEMBER(Param4) { httpRequest },									\
		PREPEND_MEMBER(Param5) { httpRequest },									\
		PREPEND_MEMBER(Param6) { httpRequest },									\
		PREPEND_MEMBER(Param7) { httpRequest },									\
		PREPEND_MEMBER(Param8) { httpRequest },									\
		PREPEND_MEMBER(Param9) { httpRequest },									\
		PREPEND_MEMBER(Param10) { httpRequest },								\
		PREPEND_MEMBER(Param11) { httpRequest }									\
	{																			\
	}																			\
																				\
	Param1& APPEND_VALUE(Param1)()												\
	{																			\
		return PREPEND_MEMBER(Param1);											\
	}																			\
																				\
	Param2& APPEND_VALUE(Param2)()												\
	{																			\
		return PREPEND_MEMBER(Param2);											\
	}																			\
																				\
	Param3& APPEND_VALUE(Param3)()												\
	{																			\
		return PREPEND_MEMBER(Param3);											\
	}																			\
																				\
	Param4& APPEND_VALUE(Param4)()												\
	{																			\
		return PREPEND_MEMBER(Param4);											\
	}																			\
																				\
	Param5& APPEND_VALUE(Param5)()												\
	{																			\
		return PREPEND_MEMBER(Param5);											\
	}																			\
																				\
	Param6& APPEND_VALUE(Param6)()												\
	{																			\
		return PREPEND_MEMBER(Param6);											\
	}																			\
																				\
	Param7& APPEND_VALUE(Param7)()												\
	{																			\
		return PREPEND_MEMBER(Param7);											\
	}																			\
																				\
	Param8& APPEND_VALUE(Param8)()												\
	{																			\
		return PREPEND_MEMBER(Param8);											\
	}																			\
																				\
	Param9& APPEND_VALUE(Param9)()												\
	{																			\
		return PREPEND_MEMBER(Param9);											\
	}																			\
																				\
	Param10& APPEND_VALUE(Param10)()											\
	{																			\
		return PREPEND_MEMBER(Param10);											\
	}																			\
																				\
	Param11& APPEND_VALUE(Param11)()											\
	{																			\
		return PREPEND_MEMBER(Param11);											\
	}																			\
																				\
private:																		\
	Param1 PREPEND_MEMBER(Param1);												\
	Param2 PREPEND_MEMBER(Param2);												\
	Param3 PREPEND_MEMBER(Param3);												\
	Param4 PREPEND_MEMBER(Param4);												\
	Param5 PREPEND_MEMBER(Param5);												\
	Param6 PREPEND_MEMBER(Param6);												\
	Param7 PREPEND_MEMBER(Param7);												\
	Param8 PREPEND_MEMBER(Param8);												\
	Param9 PREPEND_MEMBER(Param9);												\
	Param10 PREPEND_MEMBER(Param10);											\
	Param11 PREPEND_MEMBER(Param11);											\
};

#define MAKE_VIEW12(PublicName, Param1, Param2, Param3, Param4, Param5,			\
	Param6, Param7, Param8, Param9, Param10, Param11, Param12)					\
class PublicName																\
{																				\
public:																			\
	PublicName(HttpRequest& httpRequest)										\
		: PREPEND_MEMBER(Param1) { httpRequest },								\
		PREPEND_MEMBER(Param2) { httpRequest },									\
		PREPEND_MEMBER(Param3) { httpRequest },									\
		PREPEND_MEMBER(Param4) { httpRequest },									\
		PREPEND_MEMBER(Param5) { httpRequest },									\
		PREPEND_MEMBER(Param6) { httpRequest },									\
		PREPEND_MEMBER(Param7) { httpRequest },									\
		PREPEND_MEMBER(Param8) { httpRequest },									\
		PREPEND_MEMBER(Param9) { httpRequest },									\
		PREPEND_MEMBER(Param10) { httpRequest },								\
		PREPEND_MEMBER(Param11) { httpRequest },								\
		PREPEND_MEMBER(Param12) { httpRequest }									\
	{																			\
	}																			\
																				\
	Param1& APPEND_VALUE(Param1)()												\
	{																			\
		return PREPEND_MEMBER(Param1);											\
	}																			\
																				\
	Param2& APPEND_VALUE(Param2)()												\
	{																			\
		return PREPEND_MEMBER(Param2);											\
	}																			\
																				\
	Param3& APPEND_VALUE(Param3)()												\
	{																			\
		return PREPEND_MEMBER(Param3);											\
	}																			\
																				\
	Param4& APPEND_VALUE(Param4)()												\
	{																			\
		return PREPEND_MEMBER(Param4);											\
	}																			\
																				\
	Param5& APPEND_VALUE(Param5)()												\
	{																			\
		return PREPEND_MEMBER(Param5);											\
	}																			\
																				\
	Param6& APPEND_VALUE(Param6)()												\
	{																			\
		return PREPEND_MEMBER(Param6);											\
	}																			\
																				\
	Param7& APPEND_VALUE(Param7)()												\
	{																			\
		return PREPEND_MEMBER(Param7);											\
	}																			\
																				\
	Param8& APPEND_VALUE(Param8)()												\
	{																			\
		return PREPEND_MEMBER(Param8);											\
	}																			\
																				\
	Param9& APPEND_VALUE(Param9)()												\
	{																			\
		return PREPEND_MEMBER(Param9);											\
	}																			\
																				\
	Param10& APPEND_VALUE(Param10)()											\
	{																			\
		return PREPEND_MEMBER(Param10);											\
	}																			\
																				\
	Param11& APPEND_VALUE(Param11)()											\
	{																			\
		return PREPEND_MEMBER(Param11);											\
	}																			\
																				\
	Param12& APPEND_VALUE(Param12)()											\
	{																			\
		return PREPEND_MEMBER(Param12);											\
	}																			\
																				\
private:																		\
	Param1 PREPEND_MEMBER(Param1);												\
	Param2 PREPEND_MEMBER(Param2);												\
	Param3 PREPEND_MEMBER(Param3);												\
	Param4 PREPEND_MEMBER(Param4);												\
	Param5 PREPEND_MEMBER(Param5);												\
	Param6 PREPEND_MEMBER(Param6);												\
	Param7 PREPEND_MEMBER(Param7);												\
	Param8 PREPEND_MEMBER(Param8);												\
	Param9 PREPEND_MEMBER(Param9);												\
	Param10 PREPEND_MEMBER(Param10);											\
	Param11 PREPEND_MEMBER(Param11);											\
	Param12 PREPEND_MEMBER(Param12);											\
};

#define MAKE_VIEW18(PublicName, Param1, Param2, Param3, Param4, Param5,			\
	Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13,			\
	Param14, Param15, Param16, Param17, Param18)								\
class PublicName																\
{																				\
public:																			\
	PublicName(HttpRequest& httpRequest)										\
		: PREPEND_MEMBER(Param1) { httpRequest },								\
		PREPEND_MEMBER(Param2) { httpRequest },									\
		PREPEND_MEMBER(Param3) { httpRequest },									\
		PREPEND_MEMBER(Param4) { httpRequest },									\
		PREPEND_MEMBER(Param5) { httpRequest },									\
		PREPEND_MEMBER(Param6) { httpRequest },									\
		PREPEND_MEMBER(Param7) { httpRequest },									\
		PREPEND_MEMBER(Param8) { httpRequest },									\
		PREPEND_MEMBER(Param9) { httpRequest },									\
		PREPEND_MEMBER(Param10) { httpRequest },								\
		PREPEND_MEMBER(Param11) { httpRequest },								\
		PREPEND_MEMBER(Param12) { httpRequest },								\
		PREPEND_MEMBER(Param13) { httpRequest },								\
		PREPEND_MEMBER(Param14) { httpRequest },								\
		PREPEND_MEMBER(Param15) { httpRequest },								\
		PREPEND_MEMBER(Param16) { httpRequest },								\
		PREPEND_MEMBER(Param17) { httpRequest },								\
		PREPEND_MEMBER(Param18) { httpRequest }									\
	{																			\
	}																			\
																				\
	Param1& APPEND_VALUE(Param1)()												\
	{																			\
		return PREPEND_MEMBER(Param1);											\
	}																			\
																				\
	Param2& APPEND_VALUE(Param2)()												\
	{																			\
		return PREPEND_MEMBER(Param2);											\
	}																			\
																				\
	Param3& APPEND_VALUE(Param3)()												\
	{																			\
		return PREPEND_MEMBER(Param3);											\
	}																			\
																				\
	Param4& APPEND_VALUE(Param4)()												\
	{																			\
		return PREPEND_MEMBER(Param4);											\
	}																			\
																				\
	Param5& APPEND_VALUE(Param5)()												\
	{																			\
		return PREPEND_MEMBER(Param5);											\
	}																			\
																				\
	Param6& APPEND_VALUE(Param6)()												\
	{																			\
		return PREPEND_MEMBER(Param6);											\
	}																			\
																				\
	Param7& APPEND_VALUE(Param7)()												\
	{																			\
		return PREPEND_MEMBER(Param7);											\
	}																			\
																				\
	Param8& APPEND_VALUE(Param8)()												\
	{																			\
		return PREPEND_MEMBER(Param8);											\
	}																			\
																				\
	Param9& APPEND_VALUE(Param9)()												\
	{																			\
		return PREPEND_MEMBER(Param9);											\
	}																			\
																				\
	Param10& APPEND_VALUE(Param10)()											\
	{																			\
		return PREPEND_MEMBER(Param10);											\
	}																			\
																				\
	Param11& APPEND_VALUE(Param11)()											\
	{																			\
		return PREPEND_MEMBER(Param11);											\
	}																			\
																				\
	Param12& APPEND_VALUE(Param12)()											\
	{																			\
		return PREPEND_MEMBER(Param12);											\
	}																			\
																				\
	Param13& APPEND_VALUE(Param13)()											\
	{																			\
		return PREPEND_MEMBER(Param13);											\
	}																			\
																				\
	Param14& APPEND_VALUE(Param14)()											\
	{																			\
		return PREPEND_MEMBER(Param14);											\
	}																			\
																				\
	Param15& APPEND_VALUE(Param15)()											\
	{																			\
		return PREPEND_MEMBER(Param15);											\
	}																			\
																				\
	Param16& APPEND_VALUE(Param16)()											\
	{																			\
		return PREPEND_MEMBER(Param16);											\
	}																			\
																				\
	Param17& APPEND_VALUE(Param17)()											\
	{																			\
		return PREPEND_MEMBER(Param17);											\
	}																			\
																				\
	Param18& APPEND_VALUE(Param18)()											\
	{																			\
		return PREPEND_MEMBER(Param18);											\
	}																			\
																				\
private:																		\
	Param1 PREPEND_MEMBER(Param1);												\
	Param2 PREPEND_MEMBER(Param2);												\
	Param3 PREPEND_MEMBER(Param3);												\
	Param4 PREPEND_MEMBER(Param4);												\
	Param5 PREPEND_MEMBER(Param5);												\
	Param6 PREPEND_MEMBER(Param6);												\
	Param7 PREPEND_MEMBER(Param7);												\
	Param8 PREPEND_MEMBER(Param8);												\
	Param9 PREPEND_MEMBER(Param9);												\
	Param10 PREPEND_MEMBER(Param10);											\
	Param11 PREPEND_MEMBER(Param11);											\
	Param12 PREPEND_MEMBER(Param12);											\
	Param13 PREPEND_MEMBER(Param13);											\
	Param14 PREPEND_MEMBER(Param14);											\
	Param15 PREPEND_MEMBER(Param15);											\
	Param16 PREPEND_MEMBER(Param16);											\
	Param17 PREPEND_MEMBER(Param17);											\
	Param18 PREPEND_MEMBER(Param18);											\
};

#define MAKE_VIEW20(PublicName, Param1, Param2, Param3, Param4, Param5,			\
	Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13,			\
	Param14, Param15, Param16, Param17, Param18, Param19, Param20)				\
class PublicName																\
{																				\
public:																			\
	PublicName(HttpRequest& httpRequest)										\
		: PREPEND_MEMBER(Param1) { httpRequest },								\
		PREPEND_MEMBER(Param2) { httpRequest },									\
		PREPEND_MEMBER(Param3) { httpRequest },									\
		PREPEND_MEMBER(Param4) { httpRequest },									\
		PREPEND_MEMBER(Param5) { httpRequest },									\
		PREPEND_MEMBER(Param6) { httpRequest },									\
		PREPEND_MEMBER(Param7) { httpRequest },									\
		PREPEND_MEMBER(Param8) { httpRequest },									\
		PREPEND_MEMBER(Param9) { httpRequest },									\
		PREPEND_MEMBER(Param10) { httpRequest },								\
		PREPEND_MEMBER(Param11) { httpRequest },								\
		PREPEND_MEMBER(Param12) { httpRequest },								\
		PREPEND_MEMBER(Param13) { httpRequest },								\
		PREPEND_MEMBER(Param14) { httpRequest },								\
		PREPEND_MEMBER(Param15) { httpRequest },								\
		PREPEND_MEMBER(Param16) { httpRequest },								\
		PREPEND_MEMBER(Param17) { httpRequest },								\
		PREPEND_MEMBER(Param18) { httpRequest },								\
		PREPEND_MEMBER(Param19) { httpRequest },								\
		PREPEND_MEMBER(Param20) { httpRequest }									\
	{																			\
	}																			\
																				\
	Param1& APPEND_VALUE(Param1)()												\
	{																			\
		return PREPEND_MEMBER(Param1);											\
	}																			\
																				\
	Param2& APPEND_VALUE(Param2)()												\
	{																			\
		return PREPEND_MEMBER(Param2);											\
	}																			\
																				\
	Param3& APPEND_VALUE(Param3)()												\
	{																			\
		return PREPEND_MEMBER(Param3);											\
	}																			\
																				\
	Param4& APPEND_VALUE(Param4)()												\
	{																			\
		return PREPEND_MEMBER(Param4);											\
	}																			\
																				\
	Param5& APPEND_VALUE(Param5)()												\
	{																			\
		return PREPEND_MEMBER(Param5);											\
	}																			\
																				\
	Param6& APPEND_VALUE(Param6)()												\
	{																			\
		return PREPEND_MEMBER(Param6);											\
	}																			\
																				\
	Param7& APPEND_VALUE(Param7)()												\
	{																			\
		return PREPEND_MEMBER(Param7);											\
	}																			\
																				\
	Param8& APPEND_VALUE(Param8)()												\
	{																			\
		return PREPEND_MEMBER(Param8);											\
	}																			\
																				\
	Param9& APPEND_VALUE(Param9)()												\
	{																			\
		return PREPEND_MEMBER(Param9);											\
	}																			\
																				\
	Param10& APPEND_VALUE(Param10)()											\
	{																			\
		return PREPEND_MEMBER(Param10);											\
	}																			\
																				\
	Param11& APPEND_VALUE(Param11)()											\
	{																			\
		return PREPEND_MEMBER(Param11);											\
	}																			\
																				\
	Param12& APPEND_VALUE(Param12)()											\
	{																			\
		return PREPEND_MEMBER(Param12);											\
	}																			\
																				\
	Param13& APPEND_VALUE(Param13)()											\
	{																			\
		return PREPEND_MEMBER(Param13);											\
	}																			\
																				\
	Param14& APPEND_VALUE(Param14)()											\
	{																			\
		return PREPEND_MEMBER(Param14);											\
	}																			\
																				\
	Param15& APPEND_VALUE(Param15)()											\
	{																			\
		return PREPEND_MEMBER(Param15);											\
	}																			\
																				\
	Param16& APPEND_VALUE(Param16)()											\
	{																			\
		return PREPEND_MEMBER(Param16);											\
	}																			\
																				\
	Param17& APPEND_VALUE(Param17)()											\
	{																			\
		return PREPEND_MEMBER(Param17);											\
	}																			\
																				\
	Param18& APPEND_VALUE(Param18)()											\
	{																			\
		return PREPEND_MEMBER(Param18);											\
	}																			\
																				\
	Param19& APPEND_VALUE(Param19)()											\
	{																			\
		return PREPEND_MEMBER(Param19);											\
	}																			\
																				\
	Param20& APPEND_VALUE(Param20)()											\
	{																			\
		return PREPEND_MEMBER(Param20);											\
	}																			\
																				\
private:																		\
	Param1 PREPEND_MEMBER(Param1);												\
	Param2 PREPEND_MEMBER(Param2);												\
	Param3 PREPEND_MEMBER(Param3);												\
	Param4 PREPEND_MEMBER(Param4);												\
	Param5 PREPEND_MEMBER(Param5);												\
	Param6 PREPEND_MEMBER(Param6);												\
	Param7 PREPEND_MEMBER(Param7);												\
	Param8 PREPEND_MEMBER(Param8);												\
	Param9 PREPEND_MEMBER(Param9);												\
	Param10 PREPEND_MEMBER(Param10);											\
	Param11 PREPEND_MEMBER(Param11);											\
	Param12 PREPEND_MEMBER(Param12);											\
	Param13 PREPEND_MEMBER(Param13);											\
	Param14 PREPEND_MEMBER(Param14);											\
	Param15 PREPEND_MEMBER(Param15);											\
	Param16 PREPEND_MEMBER(Param16);											\
	Param17 PREPEND_MEMBER(Param17);											\
	Param18 PREPEND_MEMBER(Param18);											\
	Param19 PREPEND_MEMBER(Param19);											\
	Param20 PREPEND_MEMBER(Param20);											\
};

#define MAKE_VIEW24(PublicName, Param1, Param2, Param3, Param4, Param5,			\
	Param6, Param7, Param8, Param9, Param10, Param11, Param12, Param13,			\
	Param14, Param15, Param16, Param17, Param18, Param19, Param20,				\
	Param21, Param22, Param23, Param24)											\
class PublicName																\
{																				\
public:																			\
	PublicName(HttpRequest& httpRequest)										\
		: PREPEND_MEMBER(Param1) { httpRequest },								\
		PREPEND_MEMBER(Param2) { httpRequest },									\
		PREPEND_MEMBER(Param3) { httpRequest },									\
		PREPEND_MEMBER(Param4) { httpRequest },									\
		PREPEND_MEMBER(Param5) { httpRequest },									\
		PREPEND_MEMBER(Param6) { httpRequest },									\
		PREPEND_MEMBER(Param7) { httpRequest },									\
		PREPEND_MEMBER(Param8) { httpRequest },									\
		PREPEND_MEMBER(Param9) { httpRequest },									\
		PREPEND_MEMBER(Param10) { httpRequest },								\
		PREPEND_MEMBER(Param11) { httpRequest },								\
		PREPEND_MEMBER(Param12) { httpRequest },								\
		PREPEND_MEMBER(Param13) { httpRequest },								\
		PREPEND_MEMBER(Param14) { httpRequest },								\
		PREPEND_MEMBER(Param15) { httpRequest },								\
		PREPEND_MEMBER(Param16) { httpRequest },								\
		PREPEND_MEMBER(Param17) { httpRequest },								\
		PREPEND_MEMBER(Param18) { httpRequest },								\
		PREPEND_MEMBER(Param19) { httpRequest },								\
		PREPEND_MEMBER(Param20) { httpRequest },								\
		PREPEND_MEMBER(Param21) { httpRequest },								\
		PREPEND_MEMBER(Param22) { httpRequest },								\
		PREPEND_MEMBER(Param23) { httpRequest },								\
		PREPEND_MEMBER(Param24) { httpRequest }									\
	{																			\
	}																			\
																				\
	Param1& APPEND_VALUE(Param1)()												\
	{																			\
		return PREPEND_MEMBER(Param1);											\
	}																			\
																				\
	Param2& APPEND_VALUE(Param2)()												\
	{																			\
		return PREPEND_MEMBER(Param2);											\
	}																			\
																				\
	Param3& APPEND_VALUE(Param3)()												\
	{																			\
		return PREPEND_MEMBER(Param3);											\
	}																			\
																				\
	Param4& APPEND_VALUE(Param4)()												\
	{																			\
		return PREPEND_MEMBER(Param4);											\
	}																			\
																				\
	Param5& APPEND_VALUE(Param5)()												\
	{																			\
		return PREPEND_MEMBER(Param5);											\
	}																			\
																				\
	Param6& APPEND_VALUE(Param6)()												\
	{																			\
		return PREPEND_MEMBER(Param6);											\
	}																			\
																				\
	Param7& APPEND_VALUE(Param7)()												\
	{																			\
		return PREPEND_MEMBER(Param7);											\
	}																			\
																				\
	Param8& APPEND_VALUE(Param8)()												\
	{																			\
		return PREPEND_MEMBER(Param8);											\
	}																			\
																				\
	Param9& APPEND_VALUE(Param9)()												\
	{																			\
		return PREPEND_MEMBER(Param9);											\
	}																			\
																				\
	Param10& APPEND_VALUE(Param10)()											\
	{																			\
		return PREPEND_MEMBER(Param10);											\
	}																			\
																				\
	Param11& APPEND_VALUE(Param11)()											\
	{																			\
		return PREPEND_MEMBER(Param11);											\
	}																			\
																				\
	Param12& APPEND_VALUE(Param12)()											\
	{																			\
		return PREPEND_MEMBER(Param12);											\
	}																			\
																				\
	Param13& APPEND_VALUE(Param13)()											\
	{																			\
		return PREPEND_MEMBER(Param13);											\
	}																			\
																				\
	Param14& APPEND_VALUE(Param14)()											\
	{																			\
		return PREPEND_MEMBER(Param14);											\
	}																			\
																				\
	Param15& APPEND_VALUE(Param15)()											\
	{																			\
		return PREPEND_MEMBER(Param15);											\
	}																			\
																				\
	Param16& APPEND_VALUE(Param16)()											\
	{																			\
		return PREPEND_MEMBER(Param16);											\
	}																			\
																				\
	Param17& APPEND_VALUE(Param17)()											\
	{																			\
		return PREPEND_MEMBER(Param17);											\
	}																			\
																				\
	Param18& APPEND_VALUE(Param18)()											\
	{																			\
		return PREPEND_MEMBER(Param18);											\
	}																			\
																				\
	Param19& APPEND_VALUE(Param19)()											\
	{																			\
		return PREPEND_MEMBER(Param19);											\
	}																			\
																				\
	Param20& APPEND_VALUE(Param20)()											\
	{																			\
		return PREPEND_MEMBER(Param20);											\
	}																			\
																				\
	Param21& APPEND_VALUE(Param21)()											\
	{																			\
		return PREPEND_MEMBER(Param21);											\
	}																			\
																				\
	Param22& APPEND_VALUE(Param22)()											\
	{																			\
		return PREPEND_MEMBER(Param22);											\
	}																			\
																				\
	Param23& APPEND_VALUE(Param23)()											\
	{																			\
		return PREPEND_MEMBER(Param23);											\
	}																			\
																				\
	Param24& APPEND_VALUE(Param24)()											\
	{																			\
		return PREPEND_MEMBER(Param24);											\
	}																			\
																				\
private:																		\
	Param1 PREPEND_MEMBER(Param1);												\
	Param2 PREPEND_MEMBER(Param2);												\
	Param3 PREPEND_MEMBER(Param3);												\
	Param4 PREPEND_MEMBER(Param4);												\
	Param5 PREPEND_MEMBER(Param5);												\
	Param6 PREPEND_MEMBER(Param6);												\
	Param7 PREPEND_MEMBER(Param7);												\
	Param8 PREPEND_MEMBER(Param8);												\
	Param9 PREPEND_MEMBER(Param9);												\
	Param10 PREPEND_MEMBER(Param10);											\
	Param11 PREPEND_MEMBER(Param11);											\
	Param12 PREPEND_MEMBER(Param12);											\
	Param13 PREPEND_MEMBER(Param13);											\
	Param14 PREPEND_MEMBER(Param14);											\
	Param15 PREPEND_MEMBER(Param15);											\
	Param16 PREPEND_MEMBER(Param16);											\
	Param17 PREPEND_MEMBER(Param17);											\
	Param18 PREPEND_MEMBER(Param18);											\
	Param19 PREPEND_MEMBER(Param19);											\
	Param20 PREPEND_MEMBER(Param20);											\
	Param21 PREPEND_MEMBER(Param21);											\
	Param22 PREPEND_MEMBER(Param22);											\
	Param23 PREPEND_MEMBER(Param23);											\
	Param24 PREPEND_MEMBER(Param24);											\
};

// GET parameters
MAKE_VIEW_PARAMETER_GET_PRIMITIVE(long, GetAccountTypeView, "accountType")
MAKE_VIEW_PARAMETER_GET_PRIMITIVE(long, GetAppBinaryChecksumView, "appBinaryChecksum")
MAKE_VIEW_PARAMETER_GET_PRIMITIVE(int, GetCallNumberView, "callNum")
MAKE_VIEW_PARAMETER_GET_PRIMITIVE(int, GetCountView, "count")
MAKE_VIEW_PARAMETER_GET_PRIMITIVE(long, GetDataChecksumView, "dataChecksum")
MAKE_VIEW_PARAMETER_GET_PRIMITIVE(long, GetLastCallTimeView, "lastCallTime")
MAKE_VIEW_PARAMETER_GET_PRIMITIVE(int, GetMatchTypeIdView, "matchType_id")
MAKE_VIEW_PARAMETER_GET_PRIMITIVE(long, GetModDllChecksumView, "modDLLChecksum")
MAKE_VIEW_PARAMETER_GET_PRIMITIVE(int, GetObserverGroupIdView, "observerGroupID")
MAKE_VIEW_PARAMETER_GET_PRIMITIVE(int, GetProfileIdView, "profile_id")
MAKE_VIEW_PARAMETER_GET_PRIMITIVE(int, GetSaleTypeView, "saleType")
MAKE_VIEW_PARAMETER_GET_PRIMITIVE(int, GetSaleVersionView, "saleVersion")
MAKE_VIEW_PARAMETER_GET_PRIMITIVE(int, GetSortOrderView, "sortOrder")
MAKE_VIEW_PARAMETER_GET_PRIMITIVE(int, GetStartView, "start")
MAKE_VIEW_PARAMETER_GET_PRIMITIVE(int, GetVersionFlagsView, "versionFlags")
MAKE_VIEW_PARAMETER_GET_COMPLEX(GetConnectIdView, "connect_id")
MAKE_VIEW_PARAMETER_GET_COMPLEX(GetCountryView, "country")
MAKE_VIEW_PARAMETER_GET_COMPLEX(GetCurrencyView, "currency")
MAKE_VIEW_PARAMETER_GET_COMPLEX(GetKeyView, "key")
MAKE_VIEW_PARAMETER_GET_COMPLEX(GetMatchIdsView, "match_ids")
MAKE_VIEW_PARAMETER_GET_COMPLEX(GetModDllFileView, "modDLLFile")
MAKE_VIEW_PARAMETER_GET_COMPLEX(GetModNameView, "modName")
MAKE_VIEW_PARAMETER_GET_COMPLEX(GetModVersionView, "modVersion")
MAKE_VIEW_PARAMETER_GET_COMPLEX(GetNamesView, "names")
MAKE_VIEW_PARAMETER_GET_COMPLEX(GetProfileIdsView, "profileIDs")
MAKE_VIEW_PARAMETER_GET_COMPLEX(GetProfileIds2View, "profile_ids")
MAKE_VIEW_PARAMETER_GET_COMPLEX(GetProfileIds3View, "profileids")
MAKE_VIEW_PARAMETER_GET_COMPLEX(GetPropertyIdView, "property_id")
MAKE_VIEW_PARAMETER_GET_COMPLEX(GetRaceIdsView, "race_ids")
MAKE_VIEW_PARAMETER_GET_COMPLEX(GetSessionIdView, "sessionID")
MAKE_VIEW_PARAMETER_GET_COMPLEX(GetSignatureView, "signature")
MAKE_VIEW_PARAMETER_GET_COMPLEX(GetStatsIdsView, "statsids")
MAKE_VIEW_PARAMETER_GET_COMPLEX(GetStatGroupIdsView, "statGroup_ids")

// POST parameters
MAKE_VIEW_PARAMETER_POST_PRIMITIVE(int, PostActiveMatchIdView, "activeMatchId")
MAKE_VIEW_PARAMETER_POST_PRIMITIVE(int, PostAdvertisementIdView, "advertisementid")
MAKE_VIEW_PARAMETER_POST_PRIMITIVE(long, PostAppBinaryChecksumView, "appbinarychecksum")
MAKE_VIEW_PARAMETER_POST_PRIMITIVE(long, PostAppBinCRCView, "appBinCRC")
MAKE_VIEW_PARAMETER_POST_PRIMITIVE(long, PostAppIdView, "appID")
MAKE_VIEW_PARAMETER_POST_PRIMITIVE(long, PostAutomatchPollIdView, "automatchPoll_id")
MAKE_VIEW_PARAMETER_POST_PRIMITIVE(int, PostBroadcastView, "broadcast")
MAKE_VIEW_PARAMETER_POST_PRIMITIVE(int, PostCallNumberView, "callNum")
MAKE_VIEW_PARAMETER_POST_PRIMITIVE(int, PostClientLibVersionView, "clientLibVersion")
MAKE_VIEW_PARAMETER_POST_PRIMITIVE(int, PostCommitView, "commit")
MAKE_VIEW_PARAMETER_POST_PRIMITIVE(int, PostCRCView, "crc")
MAKE_VIEW_PARAMETER_POST_PRIMITIVE(long, PostDatachecksumView, "datachecksum")
MAKE_VIEW_PARAMETER_POST_PRIMITIVE(long, PostDataCRCView, "dataCRC")
MAKE_VIEW_PARAMETER_POST_PRIMITIVE(long, PostFromProfileIdView, "from_profile_id")
MAKE_VIEW_PARAMETER_POST_PRIMITIVE(long, PostHostIdView, "hostid")
MAKE_VIEW_PARAMETER_POST_PRIMITIVE(int, PostIsObservableView, "isObservable")
MAKE_VIEW_PARAMETER_POST_PRIMITIVE(int, PostItemLocationIdView, "itemLocation_id")
MAKE_VIEW_PARAMETER_POST_PRIMITIVE(int, PostItemInstanceIdView, "itemInstance_id")
MAKE_VIEW_PARAMETER_POST_PRIMITIVE(long, PostLastCallTimeView, "lastCallTime")
MAKE_VIEW_PARAMETER_POST_PRIMITIVE(long, PostMatchIdView, "match_id")
MAKE_VIEW_PARAMETER_POST_PRIMITIVE(long, PostMatchId2View, "matchID");
MAKE_VIEW_PARAMETER_POST_PRIMITIVE(int, PostMatchTypeView, "matchtype")
MAKE_VIEW_PARAMETER_POST_PRIMITIVE(int, PostMaxPlayersView, "maxplayers")
MAKE_VIEW_PARAMETER_POST_PRIMITIVE(int, PostMinorVersionView, "minorVersion")
MAKE_VIEW_PARAMETER_POST_PRIMITIVE(int, PostMessageIdView, "messageID")
MAKE_VIEW_PARAMETER_POST_PRIMITIVE(long, PostModDllChecksumView, "moddllchecksum")
MAKE_VIEW_PARAMETER_POST_PRIMITIVE(long, PostModDllCRCView, "modDllCRC")
MAKE_VIEW_PARAMETER_POST_PRIMITIVE(int, PostMessageTypeIdView, "messageTypeID")
MAKE_VIEW_PARAMETER_POST_PRIMITIVE(int, PostObserverDelayView, "observerDelay")
MAKE_VIEW_PARAMETER_POST_PRIMITIVE(int, PostOwnerProfileIdView, "ownerProfileID")
MAKE_VIEW_PARAMETER_POST_PRIMITIVE(int, PostPartyView, "party");
MAKE_VIEW_PARAMETER_POST_PRIMITIVE(int, PostPartySessionIdView, "partySessionID");
MAKE_VIEW_PARAMETER_POST_PRIMITIVE(int, PostPasswordedView, "passworded");
MAKE_VIEW_PARAMETER_POST_PRIMITIVE(int, PostPresenceIdView, "presence_id");
MAKE_VIEW_PARAMETER_POST_PRIMITIVE(int, PostPresencePropertyDefIdView, "presencePropertyDef_id");
MAKE_VIEW_PARAMETER_POST_PRIMITIVE(int, PostRaceView, "race");
MAKE_VIEW_PARAMETER_POST_PRIMITIVE(int, PostResultView, "result");
MAKE_VIEW_PARAMETER_POST_PRIMITIVE(int, PostResultCodeView, "resultCode");
MAKE_VIEW_PARAMETER_POST_PRIMITIVE(int, PostServiceTypeView, "serviceType");
MAKE_VIEW_PARAMETER_POST_PRIMITIVE(int, PostStateView, "state");
MAKE_VIEW_PARAMETER_POST_PRIMITIVE(int, PostStatGroupView, "statgroup");
MAKE_VIEW_PARAMETER_POST_PRIMITIVE(int, PostTeamView, "team");
MAKE_VIEW_PARAMETER_POST_PRIMITIVE(int, PostTimeoutOverrideView, "timeoutOverride");
MAKE_VIEW_PARAMETER_POST_PRIMITIVE(long, PostToProfileIdView, "to_profile_id")
MAKE_VIEW_PARAMETER_POST_PRIMITIVE(int, PostVersionFlagsView, "versionFlags")
MAKE_VIEW_PARAMETER_POST_PRIMITIVE(int, PostVisibleView, "visible")
MAKE_VIEW_PARAMETER_POST_PRIMITIVE(int, PostWithPartySessionIdView, "withPartySessionID")
MAKE_VIEW_PARAMETER_POST_COMPLEX(PostAccountTypeView, "accountType")
MAKE_VIEW_PARAMETER_POST_COMPLEX(PostAliasView, "alias")
MAKE_VIEW_PARAMETER_POST_COMPLEX(PostAuthView, "auth")
MAKE_VIEW_PARAMETER_POST_COMPLEX(PostChargesView, "charges")
MAKE_VIEW_PARAMETER_POST_COMPLEX(PostChecksumsView, "checkSums")
MAKE_VIEW_PARAMETER_POST_COMPLEX(PostChoicesView, "choices")
MAKE_VIEW_PARAMETER_POST_COMPLEX(PostConnectIdView, "connect_id")
MAKE_VIEW_PARAMETER_POST_COMPLEX(PostCountersZipView, "countersZip")
MAKE_VIEW_PARAMETER_POST_COMPLEX(PostCountryView, "country")
MAKE_VIEW_PARAMETER_POST_COMPLEX(PostDeletesView, "deletes")
MAKE_VIEW_PARAMETER_POST_COMPLEX(PostDescriptionView, "description")
MAKE_VIEW_PARAMETER_POST_COMPLEX(PostFactionIdsView, "factionIDs")
MAKE_VIEW_PARAMETER_POST_COMPLEX(PostFromItemIdsView, "fromItemIDs")
MAKE_VIEW_PARAMETER_POST_COMPLEX(PostInstallationTypeView, "installationType")
MAKE_VIEW_PARAMETER_POST_COMPLEX(PostIsNonParticipantsView, "isNonParticipants")
MAKE_VIEW_PARAMETER_POST_COMPLEX(PostItemChargesView, "itemCharges")
MAKE_VIEW_PARAMETER_POST_COMPLEX(PostItemIdsView, "itemIDs")
MAKE_VIEW_PARAMETER_POST_COMPLEX(PostItemLocationIdsView, "itemLocationIDs")
MAKE_VIEW_PARAMETER_POST_COMPLEX(PostItemLocationsView, "itemLocations")
MAKE_VIEW_PARAMETER_POST_COMPLEX(PostItemUpdatesView, "itemUpdates")
MAKE_VIEW_PARAMETER_POST_COMPLEX(PostLanguageView, "language")
MAKE_VIEW_PARAMETER_POST_COMPLEX(PostMacAddressView, "macAddress")
MAKE_VIEW_PARAMETER_POST_COMPLEX(PostMajorVersionView, "majorVersion")
MAKE_VIEW_PARAMETER_POST_COMPLEX(PostMapNameView, "mapname")
MAKE_VIEW_PARAMETER_POST_COMPLEX(PostMatchTypesView, "matchTypes")
MAKE_VIEW_PARAMETER_POST_COMPLEX(PostMessageView, "message")
MAKE_VIEW_PARAMETER_POST_COMPLEX(PostMetadataView, "metaData")
MAKE_VIEW_PARAMETER_POST_COMPLEX(PostModDllFileView, "moddllfile")
MAKE_VIEW_PARAMETER_POST_COMPLEX(PostModDllFile2View, "modDLLFile")
MAKE_VIEW_PARAMETER_POST_COMPLEX(PostModNameView, "modname")
MAKE_VIEW_PARAMETER_POST_COMPLEX(PostModName2View, "modName")
MAKE_VIEW_PARAMETER_POST_COMPLEX(PostModVersionView, "modversion")
MAKE_VIEW_PARAMETER_POST_COMPLEX(PostModVersion2View, "modVersion")
MAKE_VIEW_PARAMETER_POST_COMPLEX(PostObserverPasswordView, "observerPassword")
MAKE_VIEW_PARAMETER_POST_COMPLEX(PostOptionsView, "options")
MAKE_VIEW_PARAMETER_POST_COMPLEX(PostPasswordView, "password")
MAKE_VIEW_PARAMETER_POST_COMPLEX(PostPlatformUserIdView, "platformUserID")
MAKE_VIEW_PARAMETER_POST_COMPLEX(PostPlatformIdsView, "platformIDs")
MAKE_VIEW_PARAMETER_POST_COMPLEX(PostPlatformLobbyIdView, "platformlobbyID")
MAKE_VIEW_PARAMETER_POST_COMPLEX(PostPosIdsView, "posIDs")
MAKE_VIEW_PARAMETER_POST_COMPLEX(PostProgressIdsView, "progressIDs")
MAKE_VIEW_PARAMETER_POST_COMPLEX(PostProfileIdsView, "profileIDs")
MAKE_VIEW_PARAMETER_POST_COMPLEX(PostProfileIds2View, "profile_ids")
MAKE_VIEW_PARAMETER_POST_COMPLEX(PostRaceIdsView, "race_ids")
MAKE_VIEW_PARAMETER_POST_COMPLEX(PostRaceInfoKeyView, "raceInfoKey")
MAKE_VIEW_PARAMETER_POST_COMPLEX(PostRaceInfoProfileIdView, "raceInfoProfileID")
MAKE_VIEW_PARAMETER_POST_COMPLEX(PostRaceInfoRaceIdView, "raceInfoRaceID")
MAKE_VIEW_PARAMETER_POST_COMPLEX(PostRelayPingTimesView, "relayPingTimes")
MAKE_VIEW_PARAMETER_POST_COMPLEX(PostRelayRegionView, "relayRegion")
MAKE_VIEW_PARAMETER_POST_COMPLEX(PostRelayRegionsView, "relayRegions")
MAKE_VIEW_PARAMETER_POST_COMPLEX(PostResultsView, "results")
MAKE_VIEW_PARAMETER_POST_COMPLEX(PostSimPlayerIdsView, "simplayerIDs")
MAKE_VIEW_PARAMETER_POST_COMPLEX(PostSessionIdView, "sessionID")
MAKE_VIEW_PARAMETER_POST_COMPLEX(PostSlotInfoView, "slotinfo")
MAKE_VIEW_PARAMETER_POST_COMPLEX(PostSlotIdsView, "slotIDs")
MAKE_VIEW_PARAMETER_POST_COMPLEX(PostStatGroupIdsView, "statGroup_ids")
MAKE_VIEW_PARAMETER_POST_COMPLEX(PostStartGameTokenView, "startGameToken")
MAKE_VIEW_PARAMETER_POST_COMPLEX(PostSyncHashView, "syncHash")
MAKE_VIEW_PARAMETER_POST_COMPLEX(PostTeamIdsView, "teamIDs")
MAKE_VIEW_PARAMETER_POST_COMPLEX(PostToItemIdsView, "toItemIDs")
MAKE_VIEW_PARAMETER_POST_COMPLEX(PostTitleView, "title")
MAKE_VIEW_PARAMETER_POST_COMPLEX(PostUpdateAmountsView, "updateAmounts")
MAKE_VIEW_PARAMETER_POST_COMPLEX(PostValueView, "value")
MAKE_VIEW_PARAMETER_POST_COMPLEX(PostXpGainedView, "xpGained")

// Messages
MAKE_VIEW4(GetConnectionInfoView, GetCallNumberView, GetConnectIdView, GetLastCallTimeView, GetSessionIdView)
MAKE_VIEW4(PostConnectionInfoView, PostCallNumberView, PostConnectIdView, PostLastCallTimeView, PostSessionIdView)

MAKE_VIEW1(GetPersonalizedSaleItemsView, GetConnectionInfoView)
MAKE_VIEW1(GetAvailableCommunityEventsView, GetConnectionInfoView)
MAKE_VIEW1(GetChallengeProgressView, GetConnectionInfoView)
MAKE_VIEW1(GetPresenceDataView, GetConnectionInfoView)
MAKE_VIEW1(GetRelationshipsView, GetConnectionInfoView)
MAKE_VIEW1(GetNewsView, GetConnectionInfoView)
MAKE_VIEW1(GetItemLoadoutsView, GetConnectionInfoView)
MAKE_VIEW1(GetChatChannelsView, GetConnectionInfoView)
MAKE_VIEW1(GetOfflineMessagesView, GetConnectionInfoView)
MAKE_VIEW1(GetAutomatchMapView, GetConnectionInfoView)
MAKE_VIEW1(GetAvailableLeaderboardsView, GetConnectionInfoView)
MAKE_VIEW1(PostLogoutView, PostConnectionInfoView)

MAKE_VIEW2(GetAchievementsView, GetConnectionInfoView, GetProfileIdsView)
MAKE_VIEW2(GetRecentMatchHistoryView, GetConnectionInfoView, GetProfileIds2View)
MAKE_VIEW2(GetRecentMatchHistorySinglePlayerView, GetConnectionInfoView, GetProfileIds2View)
MAKE_VIEW2(GetScheduledSaleAndItemsView, GetConnectionInfoView, GetSaleTypeView)
MAKE_VIEW2(GetStatGroupsByProfileIdsView, GetConnectionInfoView, GetProfileIds3View)
MAKE_VIEW2(GetProfileNameView, GetConnectionInfoView, GetProfileIds2View);
MAKE_VIEW2(GetInventoryByProfileIdsView, GetConnectionInfoView, GetProfileIdsView)
MAKE_VIEW2(GetAvailableAchievementsView, GetConnectionInfoView, GetSignatureView)
MAKE_VIEW2(GetItemDefinitionsJsonView, GetConnectionInfoView, GetSignatureView)
MAKE_VIEW2(GetItemBundlesJsonView, GetConnectionInfoView, GetSignatureView)
MAKE_VIEW2(GetAdvertisementsView, GetConnectionInfoView, GetMatchIdsView)
MAKE_VIEW2(GetLevelRewardsTableJsonView, GetConnectionInfoView, GetSignatureView)
MAKE_VIEW2(GetFileUrlView, GetConnectionInfoView, GetNamesView)
MAKE_VIEW2(GetPartyStatView, GetConnectionInfoView, GetStatsIdsView)
MAKE_VIEW2(GetChallengesView, GetConnectionInfoView, GetSignatureView)
MAKE_VIEW2(GetTempCredentialsView, GetConnectionInfoView, GetKeyView)
MAKE_VIEW2(PostFindProfilesByPlatformIdView, PostConnectionInfoView, PostPlatformIdsView)
MAKE_VIEW2(PostSetPresenceView, PostConnectionInfoView, PostPresenceIdView)
MAKE_VIEW2(PostPasswordInfoView, PostPasswordView, PostPasswordedView)
MAKE_VIEW2(PostStopObservingView, PostConnectionInfoView, PostAdvertisementIdView)
MAKE_VIEW2(PostLeaveView, PostConnectionInfoView, PostAdvertisementIdView)
MAKE_VIEW2(PostSignItemsView, PostConnectionInfoView, PostCRCView)
MAKE_VIEW2(PostDeleteOfflineMessages, PostConnectionInfoView, PostMessageIdView)
MAKE_VIEW2(PostSetAvatarMetadata, PostConnectionInfoView, PostMetadataView)

MAKE_VIEW3(GetProfilePropertyView, GetConnectionInfoView, GetProfileIdView, GetPropertyIdView)
MAKE_VIEW3(PostUpdatePlatformLobbyIdView, PostConnectionInfoView, PostMatchId2View, PostPlatformLobbyIdView)
MAKE_VIEW3(PostObserverInfoView, PostObserverPasswordView, PostObserverDelayView, PostIsObservableView)
MAKE_VIEW3(PostSetPresencePropertyView, PostConnectionInfoView, PostPresencePropertyDefIdView, PostValueView)
MAKE_VIEW3(PostRaceInfoView, PostRaceInfoKeyView, PostRaceInfoProfileIdView, PostRaceInfoRaceIdView)
MAKE_VIEW3(PostRelayInfoView, PostRelayPingTimesView, PostRelayRegionView, PostRelayRegionsView)
MAKE_VIEW3(PostSyncStatsView, PostConnectionInfoView, PostAccountTypeView, PostAuthView)
MAKE_VIEW3(PostUpdateStateView, PostConnectionInfoView, PostAdvertisementIdView, PostStateView)
MAKE_VIEW3(PostStopPollingView, PostConnectionInfoView, PostCommitView, PostOwnerProfileIdView)
MAKE_VIEW3(PostUpdateProgressBatchedView, PostConnectionInfoView, PostProgressIdsView, PostUpdateAmountsView)

MAKE_VIEW4(GetModInfoView, GetModDllChecksumView, GetModDllFileView, GetModNameView, GetModVersionView)
MAKE_VIEW4(PostModInfoView, PostModDllChecksumView, PostModDllFileView, PostModNameView, PostModVersionView)
MAKE_VIEW4(PostModInfo2View, PostModDllFile2View, PostModDllCRCView, PostModName2View, PostModVersion2View)
MAKE_VIEW4(PostUpdateStatusView, PostConnectionInfoView, PostMatchId2View, PostResultView, PostResultCodeView)
MAKE_VIEW4(PostOpenItemPackView, PostConnectionInfoView, PostChoicesView, PostItemInstanceIdView, PostItemLocationIdView)
MAKE_VIEW4(PostDetachItemsView, PostConnectionInfoView, PostItemChargesView, PostItemIdsView, PostItemLocationsView)

MAKE_VIEW5(GetItemPricesView, GetConnectionInfoView, GetAccountTypeView, GetCountryView, GetCurrencyView,
	GetSaleVersionView)
MAKE_VIEW5(PostMoveChargesView, PostConnectionInfoView, PostChargesView, PostDeletesView, PostFromItemIdsView,
	PostToItemIdsView)
MAKE_VIEW5(PostMoveItemView, PostConnectionInfoView, PostItemIdsView, PostItemLocationIdsView, PostPosIdsView,
	PostSlotIdsView)

MAKE_VIEW6(PostPeerAddView, PostConnectionInfoView, PostMatchIdView, PostProfileIds2View,
	PostRaceIdsView, PostStatGroupIdsView, PostTeamIdsView)
MAKE_VIEW6(PostPeerUpdateView, PostConnectionInfoView, PostIsNonParticipantsView, PostMatchIdView,
	PostProfileIds2View, PostRaceIdsView, PostTeamIdsView)

MAKE_VIEW7(PostMatchChatMessageView, PostConnectionInfoView, PostBroadcastView, PostFromProfileIdView,
	PostMatchIdView, PostMessageView, PostMessageTypeIdView, PostToProfileIdView)

MAKE_VIEW8(PostStartObservingView, PostConnectionInfoView, PostAdvertisementIdView, PostAppBinaryChecksumView,
	PostDatachecksumView, PostModInfoView, PostPasswordView, PostVersionFlagsView, PostWithPartySessionIdView)

MAKE_VIEW9(GetFindObservableAdvertisementsView, GetConnectionInfoView, GetAppBinaryChecksumView, GetCountView,
	GetDataChecksumView, GetModInfoView, GetObserverGroupIdView, GetSortOrderView, GetStartView, GetVersionFlagsView)
MAKE_VIEW9(GetFindAdvertisementsView, GetConnectionInfoView, GetProfileIds2View, GetAppBinaryChecksumView,
		GetDataChecksumView, GetMatchTypeIdView, GetModInfoView, GetRaceIdsView, GetStatGroupIdsView, GetVersionFlagsView)

MAKE_VIEW11(PostReportMatchView, PostConnectionInfoView, PostChecksumsView, PostCountersZipView, PostItemUpdatesView,
	PostMatchIdView, PostProfileIds2View, PostRaceIdsView, PostResultsView, PostSimPlayerIdsView, PostTeamIdsView,
	PostXpGainedView)
MAKE_VIEW11(PostStartPollingView, PostConnectionInfoView, PostAppBinCRCView, PostDataCRCView, PostFactionIdsView,
	PostMatchTypesView, PostModInfo2View, PostOptionsView, PostPartySessionIdView, PostRaceInfoView,
	PostRelayInfoView, PostVersionFlagsView)
MAKE_VIEW11(PostJoinView, PostConnectionInfoView, PostAdvertisementIdView, PostAppBinaryChecksumView,
	PostDatachecksumView, PostModInfoView, PostPartyView, PostPasswordView, PostRaceView, PostStatGroupView,
	PostTeamView, PostVersionFlagsView)

MAKE_VIEW18(PostUpdateView, PostConnectionInfoView, PostAdvertisementIdView, PostAppBinaryChecksumView,
	PostAutomatchPollIdView, PostDatachecksumView, PostDescriptionView, PostHostIdView, PostObserverInfoView,
	PostMapNameView, PostMatchTypeView, PostMaxPlayersView, PostModInfoView, PostOptionsView, PostPasswordInfoView,
	PostSlotInfoView, PostStateView, PostVersionFlagsView, PostVisibleView)

MAKE_VIEW20(PostPlatformLoginView, PostAccountTypeView, PostActiveMatchIdView, PostAliasView, PostAppIdView,
	PostAuthView, PostCallNumberView, PostClientLibVersionView, PostConnectIdView, PostCountryView,
	PostInstallationTypeView, PostLanguageView, PostLastCallTimeView, PostMacAddressView, PostMajorVersionView,
	PostMinorVersionView, PostPlatformUserIdView, PostStartGameTokenView, PostSyncHashView, PostTimeoutOverrideView,
	PostTitleView)

MAKE_VIEW24(PostHostView, PostConnectionInfoView, PostAdvertisementIdView, PostAppBinaryChecksumView,
	PostAutomatchPollIdView, PostDatachecksumView, PostDescriptionView, PostHostIdView,
	PostMapNameView, PostMatchTypeView, PostMaxPlayersView,
	PostModInfoView, PostObserverInfoView, PostOptionsView, PostPartyView,
	PostPasswordInfoView, PostRaceView, PostRelayRegionView, PostServiceTypeView,
	PostSlotInfoView, PostStateView, PostStatGroupView, PostTeamView, PostVersionFlagsView,
	PostVisibleView)
}