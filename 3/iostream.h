#ifndef IOSTREAM
#define IOSTREAM

#include "minicrt.h"

namespace std {
	class ofstream
	{
	protected:
		FILE *fp;
		ofstream(const ofstream&);
	public:
		enum openmode{in = 1, out = 2, binary = 4, trunc = 8};

		ofstream();
		~ofstream();
		explicit ofstream(const char *filename, ofstream::openmode md = ofstream::out);
		ofstream& operator<<(char);
		ofstream& operator<<(int);
		ofstream& operator<<(const char*);
		ofstream& operator<<(ofstream& (*)(ofstream&));
		void open(const char *filename, ofstream::openmode md = ofstream::out);
		void close();
		ofstream &write(const char *buf, unsigned size);
	};

	inline ofstream& endl(ofstream& o) {
		return o << '\n';
	}

	class stdout_stream : public ofstream {
	public:
		stdout_stream();
	};
	extern stdout_stream cout;
}

#endif //IOSTREAM