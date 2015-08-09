#include "iostream.h"
#include "minicrt.h"
#include <Windows.h>

namespace std {
	stdout_stream cout;

	stdout_stream::stdout_stream() : ofstream() {
		fp = stdout;
	}
	
	ofstream::ofstream() : fp(0) {}
	ofstream::~ofstream() { 
		close(); 
	}
	ofstream::ofstream(const char *filename, ofstream::openmode md) : fp(0) {
		open(filename, md);
	}
	ofstream& ofstream::operator<<(char c) {
		fputc(c, fp);
		return *this;
	}
	ofstream& ofstream::operator<<(int n) {
		fprintf(fp, "%d", n);
		return *this;
	}
	ofstream& ofstream::operator<<(const char *n) {
		fprintf(fp, "%s", n);
		return *this;
	}
	ofstream& ofstream::operator<<(ofstream& (*manip)(ofstream&)) {
		return manip(*this);
	}

	void ofstream::open(const char *filename, ofstream::openmode md)
	{
		char mode[4];
		close();
		switch (md) 
		{
		case out | trunc:
			strcpy(mode, "w");
			break;
		case out | in | trunc:
			strcpy(mode, "w+");
			break;
		case out | binary | trunc:
			strcpy(mode, "wb");
			break;
		case out | in | binary | trunc:
			strcpy(mode, "wb+");
			break;
		}
		fp = fopen(filename, mode);
	}
	void ofstream::close()
	{
		if (fp) {
			fclose(fp);
			fp = 0;
		}
	}

	ofstream& ofstream::write(const char *buf, unsigned size)
	{
		fwrite(buf, 1, size, fp);
		return *this;
	}
}