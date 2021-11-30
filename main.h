#ifndef GRAPHICS101_MAIN_H
#define GRAPHICS101_MAIN_H

#ifdef DEBUG
#define logger(...) fprintf(__VA_ARGS__);
#define trace(...) printf(__VA_ARGS__);
#else
#define logger(type,message)
#define trace(message)

#endif

#endif //GRAPHICS101_MAIN_H
