class Bar;

class Foo
{
public:
	const Bar* bar() const;
};

class Bar : public Foo
{
public:
	Bar()
	{
		m_value = 2020;
	}

	int value() const
	{
		return m_value;
	}

private:
	int m_value;
};

const Bar* Foo::bar() const
{
	return static_cast<const Bar*>(this);
}

static Foo test()
{
	return Bar();
}

int main()
{
	const Bar* bar = test().bar();
	int n = bar->value();

	return n;
}
