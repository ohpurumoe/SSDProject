class IStorage {
public:
	virtual int read(int lba) = 0;
	virtual void write(int lba, int data) = 0;
};