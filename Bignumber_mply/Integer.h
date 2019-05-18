#include <string>
#include <functional>
using namespace std;

class Integer {
public:
	Integer();
	Integer(const string& input);
	~Integer();
	Integer operator+(const Integer& other) const;
	Integer operator-(const Integer& other) const;
	Integer operator*(const Integer& other) const;
	size_t size() const { return fString.size(); }
	void padRight(size_t num);
	void padLeft(size_t num);
	Integer substr(size_t pos, size_t length) const;
	void print() const;
	void stripLeadingZeros();
private:
	string fString;
};
void equalizeLengthsPadLeft(Integer& first,Integer& second);
void equalizeLengthsPadRight(string& first, string& second);