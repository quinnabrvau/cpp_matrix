//
//  Container_Multi_Level.h
//  Cpp_Matrix
//
//  Created by Quinn Abrahams-Vaughn on 1/26/19.
//

#ifndef Container_Multi_Level_h
#define Container_Multi_Level_h

#include <iterator>

namespace matrix {

    template <class cont1, class cont2, class T>
    class Container_Multi_Level:public cont1 {
        typedef typename cont1::iterator c_iterator; //column iterator
        typedef typename cont2::iterator r_iterator;              //row iterator
        typedef typename cont1::const_iterator c_iterator_const; //column iterator const
        typedef typename cont2::const_iterator r_iterator_const;              //row iterator const
        typedef cont2 row_type;
        
    public:
        
        class iterator {
            c_iterator cit, end_;
            r_iterator rit;
            int index;
        public:
            typedef std::bidirectional_iterator_tag iterator_category;
            typedef size_t difference_type;
            
            iterator(c_iterator _c_it, r_iterator _r_it, c_iterator _end, int _index) :
            cit(_c_it), end_(_end), rit(_r_it), index(_index) {}
        
            bool operator==(iterator const * const it) const{
                if (cit == end_ && it->cit == end_)
                    return true;
                if (this->cit != it->cit)
                    return false;
                if (this->rit != it->rit)
                    return false;
                return true;
            }
            bool operator!=(iterator const * const it) const{
                if (cit == end_ && it->cit == end_)
                    return false;
                if (this->cit == it->cit && this->rit == it->rit)
                    return false;
                return true;
            }
            
            bool operator==(iterator const &it) const{
                if (cit == end_ && it.cit == end_)
                    return true;
                if (this->cit != it.cit)
                    return false;
                if (this->rit != it.rit)
                    return false;
                return true;
            }
            bool operator!=(iterator const &it) const{
                if (cit == end_ && it.cit == end_)
                    return false;
                if (this->cit == it.cit && this->rit == it.rit)
                    return false;
                return true;
            }
            void next(void) {
                if (cit == end_)
                    return;
                rit++;
                index++;
                if (rit == (*cit).end()) {
                    cit++;
                    if (cit != end_) {
                        rit = (*cit).begin();
                        index = 0;
                    }
                }
            }
            void prev(void) {
                if (rit == (*cit).begin() ||
                    cit == end_ ) {
                    cit--;
                    rit = (*cit).end();
                    rit--;
                    index = (*cit).size();
                } else {
                    rit--;
                    index--;
                }
                if (index < 0) {
                    index--;
                }
            }
            iterator operator++(void) {
                this->next(); return *this;
            }
            iterator operator++(int junk) {
                iterator out = *this;
                this->next();
                return out;
            }
            iterator operator--(void) {
                this->prev(); return *this;
            }
            iterator operator--(int junk) {
                iterator out = *this;
                this->prev();
                return out;
            }

            T& operator*(void) {
                return (*rit);
            }
            T* operator->(void) {
                return rit.operator->();
            }
            
            void operator*=(int junk) {
                cit++;
                rit = (*cit).begin();
                for (int i = 0; i < index; i++) {
                    rit++;
                }
            }
            r_iterator begin(void) {
                return (*cit).begin();
            }
            r_iterator end(void) {
                return (*cit).end();
            }
        };
    
        class const_iterator {
            c_iterator_const cit, end_;
            r_iterator_const rit;
            int index;
        public:
            typedef std::bidirectional_iterator_tag iterator_category;
            typedef size_t difference_type;
            
            const_iterator(c_iterator_const _c_it, r_iterator_const _r_it, c_iterator_const _end, int _index) :
                cit(_c_it), end_(_end), rit(_r_it), index(_index) {}
            
            bool operator==(const_iterator const * const it) const{
                if (cit == end_ && it->cit == end_)
                    return true;
                if (this->cit != it->cit)
                    return false;
                if (this->rit != it->rit)
                    return false;
                return true;
            }
            bool operator!=(const_iterator const * const it) const{
                if (cit == end_ && it->cit == end_)
                    return false;
                if (this->cit == it->cit && this->rit == it->rit)
                    return false;
                return true;
            }
            
            bool operator==(const_iterator const &it) const{
                if (cit == end_ && it.cit == end_)
                    return true;
                if (this->cit != it.cit)
                    return false;
                if (this->rit != it.rit)
                    return false;
                return true;
            }
            bool operator!=(const_iterator const &it) const{
                if (cit == end_ && it.cit == end_)
                    return false;
                if (this->cit == it.cit && this->rit == it.rit)
                    return false;
                return true;
            }
            
            void next(void) {
                if (cit == end_)
                    return;
                rit++;
                index++;
                if (rit == (*cit).end()) {
                    cit++;
                    if (cit != end_) {
                        rit = (*cit).begin();
                        index = 0;
                    }
                }
            }
            void prev(void) {
                if (rit == (*cit).begin() ||
                    cit == end_ ) {
                    cit--;
                    rit = (*cit).end();
                    rit--;
                    index = (*cit).size();
                } else {
                    rit--;
                    index--;
                }
                if (index < 0) {
                    index--;
                }
            }
            
            const_iterator operator++(void) {
                this->next(); return *this;
            }
            const_iterator operator++(int junk) {
                const_iterator out = *this;
                this->next();
                return out;
            }
            const_iterator operator--(void) {
                this->prev(); return *this;
            }
            const_iterator operator--(int junk) {
                const_iterator out = *this;
                this->prev();
                return out;
            }
            const T& operator*(void) const {
                return (*rit);
            }
            const T* operator->(void) {
                return rit.operator->();
            }
            r_iterator_const begin(void) {
                return (*cit).begin();
            }
            r_iterator_const end(void) {
                return (*cit).end();
            }
        };
        
        // Iterator Creator
        iterator begin(void) {
            c_iterator c_it = cont1::begin();
            r_iterator r_it = (*c_it).begin();
            c_iterator c_end = cont1::end();
            return iterator(c_it,r_it,c_end,0);
        }
        iterator end(void) {
            c_iterator c_it = cont1::end();
            r_iterator r_it = cont1::back().end();
            c_iterator c_end = cont1::end();
            return iterator(c_it,r_it,c_end,cont1::back().size());
        }
        const_iterator begin(void) const {
            c_iterator_const c_it = cont1::cbegin();
            r_iterator_const r_it = (*c_it).cbegin();
            c_iterator_const c_end = cont1::cend();
            return const_iterator(c_it,r_it,c_end,0);
        }
        const_iterator end(void) const {
            c_iterator_const c_it = cont1::cend();
            r_iterator_const r_it = cont1::back().cend();
            c_iterator_const c_end = cont1::cend();
            return const_iterator(c_it, r_it, c_end, cont1::back().size());
        }
        const_iterator cbegin(void) const {
            c_iterator_const c_it = cont1::cbegin();
            r_iterator_const r_it = (*c_it).cbegin();
            c_iterator_const c_end = cont1::cend();
            return const_iterator(c_it, r_it, c_end, 0);
        }
        const_iterator cend(void) const {
            c_iterator_const c_it = cont1::cend();
            r_iterator_const r_it = cont1::back().cend();
            c_iterator_const c_end = cont1::cend();
            return const_iterator(c_it, r_it, c_end, cont1::back().size());
        }
        
        Container_Multi_Level (iterator be, iterator end): cont1() {
            cont1::clear();
            while (be != end) {
                cont1::push_back(row_type(be.begin(),be.end()));
                be*=1;
            }
        }
        Container_Multi_Level (const_iterator be, const_iterator end): cont1() {
            cont1::clear();
            while (be != end) {
                cont1::push_back(row_type(be.cbegin(),be.cend()));
                be*=1;
            }
        }
        
        Container_Multi_Level(): cont1() {};
        
        Container_Multi_Level(c_iterator be, c_iterator end) :
        cont1(be,end) {}
        Container_Multi_Level(c_iterator_const be, c_iterator_const end) :
        cont1(be,end) {}
        
        Container_Multi_Level(int size): cont1(size) {};
        
        Container_Multi_Level(int size1, int size2): cont1(size1) {
            c_iterator it = cont1::begin();
            while(it != cont1::end()) {
                (*it++) = cont2(size2);
            }
        };
    };
}

void test__CML(void);

#define CML1(cont, type)            \
    Container_Multi_Level<cont<cont<type>>,cont<type>,type>

#define CML2(cont1, cont2, type)    \
    Container_Multi_Level<cont1<cont2<type>>,cont2<type>,type>


#endif /* Container_Multi_Level_h */
