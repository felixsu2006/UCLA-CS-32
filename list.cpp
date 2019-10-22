

void listAll(const MenuItem* m, string path) // two-parameter overload
{
	const vector<MenuItem*>* temp = m->menuItems();
	if (path == "")
	{
		path = m->name();
		cout << path << endl;
	}
	else
	{
		path = path + "/" + m->name();
		cout << path << endl;
	}
	if (temp == nullptr)
	{
		return;
	}

	for (int k = 0; k < temp->size(); k++)
	{
		listAll((*temp)[k], path);
	}
	

}

