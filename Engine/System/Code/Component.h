#pragma once

BEGIN(Engine)


class ENGINE_DLL Component abstract
{
protected:
	explicit Component(void);
public:
	virtual ~Component(void) PURE;

public:
	virtual void Update(void) PURE;
	virtual void Render(void) PURE;
};


END