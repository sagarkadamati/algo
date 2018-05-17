#ifndef __BC_STREAM__
#define __BC_STREAM__

#define STREAM_NAME_SIZE	20

#define DEFINE_STREAM_HEADER(_name, _max_vstreams)	\
	struct _name {									\
		char name[STREAM_NAME_SIZE];				\
		int  enable;								\
													\
		int sindex[_max_vstreams];					\
													\
		int streams_offset;							\
		int streams_size;							\
		int streams_count;							\
													\
		int cmds_count;								\
	} __attribute__ ((packed))

#define DEFINE_STREAM(_name, _size)					\
	struct _name {									\
		char name[STREAM_NAME_SIZE];				\
													\
		int enable;									\
		int used;									\
													\
		int id;										\
		int type;									\
		int sid;									\
		pid_t pid;									\
													\
		command cmds[_size];						\
	} __attribute__ ((packed))

typedef struct stream {
	int sid;
	int soffset;
	int ssize;
} __attribute__ ((packed)) stream;

#define STREAM_SIZE(_x)								\
	(sizeof(stream))

#define STREAM_DATA(_t, _s)	(_t->mblock + _s->soffset)

#endif /* __BC_STREAM__ */
