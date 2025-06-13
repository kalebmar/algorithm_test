# protecta_test


1. Two files (A and B) are given. Check if file B starts with the same bytes as the whole file A
(can return true if B is bigger) using checksum calculation.
- Files can be bigger than the memory available
- Assume a predefined function is available for checksum calculation: uint32_t
MyChkSum(const char* buff, size_t len, uint32_t prevchk)
- MyChkSum can calculate only 1024 bytes (len <= 1024), must be called
multiple times for larger files
- prevchk must set to previous result of MyChkSum, or to 0 for the first run
- B can be much bigger (e.g.: check header in a several GB media file), avoid reading
the whole B if not necessary.
- Implement the following function:
bool Compare(const std::string& p_A_filename, const std::string& p_B_filename)
returns true if B starts with the same bytes as the whole A file

2. A set of points on a plane is given. Each point is identified by its x and y coordinates and a
text identifier (id). More than one point can share the same identifier (coordinates can be
different).
- implement the following function:
float CalculateBiggestRadius(const std::vector<Point>& points) - the function should
return the radius of the largest circle centred at origin (x=0,y=0) in which the identifier
of every point is unique. A point is inside the circle if the distance from origin is
less than the radius!!!! Write the algorithm in C++!
