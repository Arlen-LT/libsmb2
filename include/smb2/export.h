
#ifndef SMB2_EXPORT_H
#define SMB2_EXPORT_H

#if defined (_WIN32)
# define SMB2_EXPORT __declspec(dllexport)
#elif defined (__GNUC__)
# define SMB2_EXPORT __attribute__((visibility("default")))
#else
# define SMB2_EXPORT
#endif

#endif /* SMB2_EXPORT_H */
