#ifndef DATA_H
# define DATA_H

# include <string>

class Data {
public:
	Data();
	Data(const Data& src);
	~Data();
	Data& operator=(const Data&);
	std::string getName() const;
	int getID() const;
private:
	int m_id;
	std::string m_name;
};

#endif
