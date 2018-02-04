#pragma once

BEGIN(Engine)


class ENGINE_DLL Component abstract
{
public :
	enum class EType
	{
		TYPE_TRANSFORM,

		TYPE_MAX
	};

protected:
	explicit Component(void);
public:
	virtual ~Component(void) PURE;

public:
	virtual void Update(void) {};
};


END