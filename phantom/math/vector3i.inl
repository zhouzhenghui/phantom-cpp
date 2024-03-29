
inline vector3<int>::vector3 ()
{
	// Uninitialized for performance in array construction.
}


inline vector3<int>::vector3 (const vector3<int>& vec)
{
	m[0] = vec.m[0];
    m[1] = vec.m[1];
    m[2] = vec.m[2];
}


inline vector3<int>::vector3 (int x, int y, int z)
{
	m[0] = x;
    m[1] = y;
    m[2] = z;
}

inline vector3<int>& vector3<int>::operator= (const vector3<int>& vec)
{
    m[0] = vec.m[0];
    m[1] = vec.m[1];
    m[2] = vec.m[2];
    return *this;
}


inline vector3<int> vector3<int>::operator+ (const vector3<int>& vec) const
{
    return vector3<int>
    (
    m[0] + vec.m[0],
    m[1] + vec.m[1],
        m[2] + vec.m[2]
    );
}


inline vector3<int> vector3<int>::operator- (const vector3<int>& vec) const
{
    return vector3<int>
    (
        m[0] - vec.m[0],
        m[1] - vec.m[1],
        m[2] - vec.m[2]
    );
}



inline vector3<int> vector3<int>::operator* (int scalar) const
{
    return vector3<int>
    (
        scalar*m[0],
        scalar*m[1],
        scalar*m[2]
    );
}


inline vector3<int> vector3<int>::operator*( const vector3<int>& vec ) const 
{
    vector3<int> result; 
    
    result.m[0] = m[0]*vec.m[0];
    result.m[1] = m[1]*vec.m[1];
    result.m[2] = m[2]*vec.m[2];
    
    return result;
}


inline vector3<int> vector3<int>::operator/ (int integer) const
{
    vector3<int> result;

    if (integer != (int)0)
    {
        result.m[0] = m[0]/integer;
        result.m[1] = m[1]/integer;
        result.m[2] = m[2]/integer;
    }
    else
    {
        result.m[0] = INT_MAX;
        result.m[1] = INT_MAX;
        result.m[2] = INT_MAX;
    }

    return result;
}


inline vector3<int> vector3<int>::operator/ ( const vector3<int>& vec ) const
{
    vector3<int> result;
    
    result.m[0] = m[0]/vec.m[0];
    result.m[1] = m[1]/vec.m[1];
    result.m[2] = m[2]/vec.m[2];

    return result;
}


inline vector3<int> vector3<int>::operator- () const
{
    return vector3<int>
    (
        -m[0],
        -m[1],
        -m[2]
    );
}


inline vector3<int>& vector3<int>::operator+= (const vector3<int>& vec)
{
    m[0] += vec.m[0];
    m[1] += vec.m[1];
    m[2] += vec.m[2];
    return *this;
}


inline vector3<int>& vector3<int>::operator-= (const vector3<int>& vec)
{
    m[0] -= vec.m[0];
    m[1] -= vec.m[1];
    m[2] -= vec.m[2];
    return *this;
}


inline vector3<int>& vector3<int>::operator*= (int scalar)
{
    m[0] *= scalar;
    m[1] *= scalar;
    m[2] *= scalar;
    return *this;
}


inline vector3<int>& vector3<int>::operator*= (const vector3<int>& vec)
{
    m[0] *= vec.x;
    m[1] *= vec.y;
    m[2] *= vec.z;
    return *this;
}


inline vector3<int>& vector3<int>::operator/= (int scalar)
{
    if (scalar != (int)0)
    {
        m[0] /= scalar;
        m[1] /= scalar;
        m[2] /= scalar;
    }
    else
    {
        m[0] *= INT_MAX;
        m[1] *= INT_MAX;
        m[2] *= INT_MAX;
    }

    return *this;
}
inline vector3<int> operator* (int scalar, const vector3<int>& vec)
{
    return vector3<int>
    (
        scalar*vec[0],
        scalar*vec[1],
        scalar*vec[2]
    );
}


inline std::ostream& operator<< (std::ostream& outFile, const vector3<int>& vec)
{
     return outFile << '(' << vec.x << ',' << vec.y << ',' << vec.z << ')';
}

