#ifndef vector_HPP
#define vector_HPP

struct subvector ;

bool init(subvector* vp) ;

void destructor(subvector* vp) ;

bool resize(subvector* vp, unsigned int new_capacity) ;

bool push_back(subvector* vp, int elem) ;

void shrink_to_fit(subvector* vp) ;

int pop_back(subvector* vp) ;

void clear(subvector* vp) ;

#endif // vector_HPP