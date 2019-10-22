

class Landmark
{
public:
	Landmark(string nameOf)
	{
		m_name = nameOf;
	}
	virtual string color() const
	{
		return "yellow";
	}
	virtual string icon() const = 0;
	string name() const
	{
		return m_name;
	}
	virtual ~Landmark()
	{}
	
private:
	string m_name;
};

class Hotel : public Landmark
{
public:
	Hotel(string nameOf)
		:Landmark(nameOf)
	{}
	virtual ~Hotel()
	{
		cout << "Destroying the hotel " << name() << "." << endl;
	}
	virtual string icon() const
	{
		return "bed";
	}
};

class Restaurant : public Landmark
{
public:
	Restaurant(string nameOf, int num)
		:Landmark(nameOf), m_num(num)
	{}
	virtual ~Restaurant()
	{
		cout << "Destroying the restaurant " << name() << "." << endl;
	}
	virtual string icon() const
	{
		if (m_num < 40)
			return "small knife/fork";
		else
			return "large knife/fork";
	}
private:
	int m_num;
};


class Hospital : public Landmark
{
public:
	Hospital(string nameOf)
		:Landmark(nameOf)
	{}
	virtual ~Hospital()
	{
		cout << "Destroying the hospital " << name() << "." << endl;
	}
	virtual string icon() const
	{
		return "H";
	}
	virtual string color() const
	{
		return "blue";
	}
};


void display(const Landmark* lm)
{
	cout << "Display a " << lm->color() << " " << lm->icon() << " icon for "
		<< lm->name() << "." << endl;
}

