#ifndef FIXED_POINT_ARITHMETIC

#define FIXED_POINT_ARITHMETIC

#define PI_FIXED_INT (int)823550
#define TWO_PI_FIXED_INT (int)1647099
#define HALF_PI_FIXED_INT (int)411775

class Fixed
{

    public:
        int value;

        Fixed()
        {
            value = 0;
        }

        Fixed(int val, bool no_cast = false)
        {
            if(no_cast)
                value = val;
            else
                value = (val << 18);
        }

        Fixed(float val)
        {
            value = ((int)(val * 262144));
        }

        Fixed(double val)
        {
            value = ((int)(val * 262144));
        }

        Fixed(const Fixed& val)
        {
            value = val.value;
        }
        
        operator int() const 
        {
            return value >> 18;
        }

        operator short() const
        {
            return (short int)(value >> 18);
        }

        operator float() const
        {
            return (((float)value) / 262144);
        }

        operator double() const
        {
            return (((double)value) / 262144);
        }

        // Fixed on Fixed

        Fixed operator +(const Fixed& other)
        {
            Fixed temp;
            temp.value = value + other.value;
            return temp;
        }
 
        Fixed operator -(Fixed other)
        {
            Fixed temp;
            temp.value = value - other.value;
            return temp;
        }

        Fixed operator *(Fixed other)
        {
            Fixed temp;

            temp.value = (int)((((signed long long)(value)) * ((signed long long)(other.value))) >> 18);

            return temp;
        }

        Fixed operator /(Fixed other)
        {
            Fixed temp;

            temp.value = (int)((((signed long long)(value)) << 18) / other.value);

            return temp;
        }
        

        Fixed operator +=(Fixed other)
        {
            value += other.value;
            return *this;
        }

        Fixed operator -=(Fixed other)
        {
            value -= other.value;
            return *this;
        }

        Fixed operator *=(Fixed other)
        {
            value = (int)((((signed long long)(value)) * ((signed long long)(other.value))) >> 18);
            return *this;
        }

        Fixed operator /=(Fixed other)
        {   
            value = (int)((((signed long long)(value)) << 18) / (signed long long)other.value);
            return *this;
        }

        // Fixed on int

        Fixed operator +(int intValue)
        {
            Fixed temp;
            temp.value = value + (intValue << 18);
            return temp;
        }

        Fixed operator -(int intValue)
        {
            Fixed temp;
            temp.value = value - (intValue << 18);
            return temp;
        }

        Fixed operator *(int intValue)
        {
            return Fixed(value * intValue, true);
        }

        Fixed operator /(int intValue)
        {
            return Fixed((value) / intValue, true);
        }
        

        Fixed operator +=(int intValue)
        {
            value += (intValue << 18);
            return *this;
        }

        Fixed operator -=(int intValue)
        {
            value -= (intValue << 18);
            return *this;
        }

        Fixed operator *=(int intValue)
        {
            value = value * intValue;
            return *this;
        }

        Fixed operator /=(int intValue)
        {
            value = value / intValue;
            return *this;
        }

        // Fixed on float

        Fixed operator +(float floatValue)
        {
            Fixed temp;

            temp.value = value + ((int)(floatValue * 262144));

            return temp;
        }

        Fixed operator -(float floatValue)
        {
            Fixed temp;

            temp.value = value - ((int)(floatValue * 262144));
            
            return temp;
        }

        Fixed operator *(float floatValue)
        {
            Fixed temp;

            temp.value = (int)(((((signed long long)(value)) * (signed long long)(Fixed(floatValue).value)) >> 18));
            
            return temp;
        }

        Fixed operator /(float floatValue)
        {
            Fixed temp;

            temp.value = (int)((((signed long long)(value) << 18) / (signed long long)(Fixed(floatValue)).value));
            
            return temp;
        }
        

        Fixed operator +=(float floatValue)
        {
            value = value + Fixed(floatValue).value;

            return *this;
        }

        Fixed operator -=(float floatValue)
        {
            value = value - Fixed(floatValue).value;
            
            return *this;
        }

        Fixed operator *=(float floatValue)
        {
            value = (int)(((((signed long long)(value)) * (signed long long)(Fixed(floatValue).value)) >> 18));
            
            return *this;
        }

        Fixed operator /=(float floatValue)
        {
            value = (int)((((signed long long)(value) << 18) / (signed long long)(Fixed(floatValue)).value));
            
            return *this;
        }
        

        // Fixed on double

        Fixed operator +(double floatValue)
        {
            Fixed temp;

            temp.value = value + ((int)(floatValue * 262144));

            return temp;
        }

        Fixed operator -(double floatValue)
        {
            Fixed temp;

            temp.value = value - ((int)(floatValue * 262144));
            
            return temp;
        }

        Fixed operator *(double floatValue)
        {
            Fixed temp;

            temp.value = (int)(((((signed long long)(value)) * (signed long long)(Fixed(floatValue).value)) >> 18));
            
            return temp;
        }

        Fixed operator /(double floatValue)
        {
            Fixed temp;

            temp.value = (int)((((signed long long)(value) << 18) / (signed long long)(Fixed(floatValue).value)));
            
            return temp;
        }
        

        Fixed operator +=(double floatValue)
        {
            value = value + Fixed(floatValue).value;

            return *this;
        }

        Fixed operator -=(double floatValue)
        {
            value = value - Fixed(floatValue).value;

            return *this;
        }

        Fixed operator *=(double floatValue)
        {
            value = (int)(((((signed long long)(value)) * (signed long long)(Fixed(floatValue).value)) >> 18));
            
            return *this;
        }

        Fixed operator /=(double floatValue)
        {
            value = (int)((((signed long long)(value) << 18) / (signed long long)(Fixed(floatValue).value)));
            
            return *this;
        }

        
        // Comparasion (Fixed on Fixed)

        bool operator ==(Fixed other)
        {
            return (value == other.value);
        }

        bool operator !=(Fixed other)
        {
            return (value != other.value);
        }

        bool operator >(Fixed other)
        {
            return (value > other.value);
        }

        bool operator <(Fixed other)
        {
            return (value < other.value);
        }

        bool operator >=(Fixed other)
        {
            return (value >= other.value);
        }

        bool operator <=(Fixed other)
        {
            return (value <= other.value);
        }
        

        // Comparasion (Fixed on float)

        bool operator ==(float other)
        {
            return (value == (Fixed(other)).value);
        }

        bool operator !=(float other)
        {
            return (value != (Fixed(other)).value);
        }

        bool operator >(float other)
        {
            return (value > (Fixed(other)).value);
        }

        bool operator <(float other)
        {
            return (value < (Fixed(other)).value);
        }

        bool operator >=(float other)
        {
            return (value >= (Fixed(other)).value);
        }

        bool operator <=(float other)
        {
            return (value <= Fixed(other).value);
        }


        // Comparasion (Fixed on double)

        bool operator ==(double other)
        {
            return (value == (Fixed(other)).value);
        }

        bool operator !=(double other)
        {
            return (value != (Fixed(other)).value);
        }

        bool operator >(double other)
        {
            return (value > (Fixed(other)).value);
        }

        bool operator <(double other)
        {
            return (value < (Fixed(other)).value);
        }

        bool operator >=(double other)
        {
            return (value >= (Fixed(other)).value);
        }

        bool operator <=(double other)
        {
            return (value <= Fixed(other).value);
        }

        // Comparasion (Fixed on int)

        bool operator ==(int other)
        {
            return (value == Fixed(other).value);
        }

        bool operator !=(int other)
        {
            return (value != Fixed(other).value);
        }

        bool operator >(int other)
        {
            return (value > Fixed(other).value);
        }

        bool operator <(int other)
        {
            return (value < Fixed(other).value);
        }

        bool operator >=(int other)
        {
            return (value >= Fixed(other).value);
        }

        bool operator <=(int other)
        {
            return (value <= Fixed(other).value);
        }
        

        // Other math

        Fixed operator+()
        {
            return Fixed(value, true);
        }

        Fixed operator-()
        {
            return Fixed(-value, true);
        }

        Fixed floor()
        {
            return Fixed((value >> 18));
        }

        int floor2int()
        {
            return value >> 18;
        }

        int ceil2int()
        {
            int decimals = value & 0b111111111111111111;

            int floored = value >> 18;

            if(decimals != 0)
                floored++;
            
            return floored;
        }

        int round2int()
        {
            return (value + 131072) >> 18;
        }

        /// @brief Maps val from range [min, max1] to the range [min2, max2]
        /// @param val 
        /// @param min1 
        /// @param max1 
        /// @param min2 
        /// @param max2 
        /// @return 
        static Fixed map(Fixed val, Fixed min1, Fixed max1, Fixed min2, Fixed max2)
        {
            return min2 + (val - min1) * (max2 - min2) / (max1 - min1);
        }

        static Fixed inverse_sqrt(Fixed number)
        {
            float floating = (float)number / (float)262144;
            long i;
            float x2, y;
            const float threehalfs = 1.5F;

            x2 = floating * 0.5F;
            y  = floating;
            i  = * ( long * ) &y;                       // evil floating point bit level hacking
            i  = 0x5f3759df - ( i >> 1 );               // what the fuck?
            y  = * ( float * ) &i;
            y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
        //	y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed

            return Fixed(y);
        }


        static Fixed sin(Fixed angle)
        {
            int temp_val = angle.value % TWO_PI_FIXED_INT;
            Fixed apropriate = Fixed(temp_val, true);
            return evaluate_sin(apropriate);
        }

        static Fixed cos(Fixed angle)
        {
            int temp_val = (angle.value + HALF_PI_FIXED_INT) % TWO_PI_FIXED_INT;
            Fixed apropriate = Fixed(temp_val, true);
            return evaluate_sin(apropriate);
        }
    
    private:
        
        static Fixed evaluate_sin(Fixed angle)
        {
            bool flip_sign = false;

            if(angle.value < -TWO_PI_FIXED_INT || angle.value > TWO_PI_FIXED_INT)
                return Fixed(-1);
            
            if(angle.value < 0)
            {
                flip_sign = true;
                angle.value = -angle.value;
            }

            if(angle.value > PI_FIXED_INT)
            {
                flip_sign = !flip_sign;
                angle.value -= PI_FIXED_INT;
            }
            
            if(angle.value > HALF_PI_FIXED_INT)
            {
                angle.value = HALF_PI_FIXED_INT - (angle.value - HALF_PI_FIXED_INT);
            }

            Fixed result = Fixed();
            
            if(angle.value < (int)235373)
            {
                result.value = angle.value;
                result = result - (angle * angle * angle) / (int)6;
                result = result + (angle * angle * angle * angle * angle) / (int)120;
                result = result - (angle * angle * angle * angle * angle * angle * angle) / (int)5040;
            }
            else
            {
                Fixed sincos_angle = Fixed(HALF_PI_FIXED_INT - angle.value, true);
                result.value = 262144;
                result = result - (sincos_angle * sincos_angle) / (int)2;
                result = result + (sincos_angle * sincos_angle * sincos_angle * sincos_angle) / (int)24;
                result = result - (sincos_angle * sincos_angle * sincos_angle * sincos_angle * sincos_angle * sincos_angle) / (int)720;
            }

            if(flip_sign)
                return -result;
            
            return result;
        }

};


class Vector2fix
{
    public:
        Fixed x;
        Fixed y;

        Vector2fix()
        {
            Vector2fix::x = 0;
            Vector2fix::y = 0;
        }
        Vector2fix(const Vector2fix& other)
        {
            Vector2fix::x = other.x;
            Vector2fix::y = other.y;
        }
        Vector2fix(int x, int y)
        {
            Vector2fix::x = Fixed(x);
            Vector2fix::y = Fixed(y);
        }
        Vector2fix(float x, float y)
        {
            Vector2fix::x = Fixed(x);
            Vector2fix::y = Fixed(y);
        }
        Vector2fix(double x, double y)
        {
            Vector2fix::x = Fixed(x);
            Vector2fix::y = Fixed(y);
        }
        Vector2fix(Fixed x, Fixed y)
        {
            Vector2fix::x = Fixed(x);
            Vector2fix::y = Fixed(y);
        }

        // Vector2fix on Vector2fix

        Vector2fix operator +(Vector2fix other)
        {
            return Vector2fix(x + other.x, y + other.y);
        }
        
        Vector2fix operator -(Vector2fix other)
        {
            return Vector2fix(x - other.x, y - other.y);
        }
        

        Vector2fix operator +=(Vector2fix other)
        {
            x += other.x;
            y += other.y;
            return *this;
        }
        
        Vector2fix operator -=(Vector2fix other)
        {
            x -= other.x;
            y -= other.y;
            return *this;
        }


        // Vector2fix on float

        Vector2fix operator *(float other)
        {
            return Vector2fix(x * Fixed(other), y * Fixed(other));
        }

        Vector2fix operator /(float other)
        {
            return Vector2fix(x / Fixed(other), y / Fixed(other));
        }

        Vector2fix operator *=(float other)
        {
            x *= Fixed(other);
            y *= Fixed(other);
            return *this;
        }

        Vector2fix operator /=(float other)
        {
            x /= Fixed(other);
            y /= Fixed(other);
            return *this;
        }

        // Vector2fix on double

        Vector2fix operator *(double other)
        {
            return Vector2fix(x * Fixed(other), y * Fixed(other));
        }

        Vector2fix operator /(double other)
        {
            return Vector2fix(x / Fixed(other), y / Fixed(other));
        }

        Vector2fix operator *=(double other)
        {
            x *= Fixed(other);
            y *= Fixed(other);
            return *this;
        }

        Vector2fix operator /=(double other)
        {
            x /= Fixed(other);
            y /= Fixed(other);
            return *this;
        }

        // Vector2fix on double

        Vector2fix operator *(Fixed other)
        {
            return Vector2fix(x * other, y * other);
        }

        Vector2fix operator /(Fixed other)
        {
            return Vector2fix(x / other, y / other);
        }

        Vector2fix operator *=(Fixed other)
        {
            x *= other;
            y *= other;
            return *this;
        }

        Vector2fix operator /=(Fixed other)
        {
            x /= other;
            y /= other;
            return *this;
        }

        // Vector2fix on int

        Vector2fix operator *(int other)
        {
            return Vector2fix(x * Fixed(other), y * Fixed(other));
        }

        Vector2fix operator /(int other)
        {
            return Vector2fix(x / Fixed(other), y / Fixed(other));
        }

        Vector2fix operator *=(int other)
        {
            x *= Fixed(other);
            y *= Fixed(other);
            return *this;
        }

        Vector2fix operator /=(int other)
        {
            x /= Fixed(other);
            y /= Fixed(other);
            return *this;
        }

        // Other

        Vector2fix operator =(const Vector2fix& other)
        {
            x = other.x;
            y = other.y;
            return *this;
        }

        Vector2fix operator +()
        {
            return Vector2fix(x, y);
        }

        Vector2fix operator -()
        {
            return Vector2fix(-x, -y);
        }

        float operator [](int index)
        {
            if(index == 0)
                return x;
            else if(index == 1)
                return y;
            else
                return 0;
        }

        Vector2fix normalized()
        {
            Fixed inverse_len = Fixed::inverse_sqrt((x * x) + (y * y));
            return Vector2fix(x * inverse_len, y * inverse_len);
        }

        Fixed dot(const Vector2fix &other)
        {
            return x * other.x + y * other.y;
        }

        Fixed cross(const Vector2fix &other)
        {
            return x * other.y - y * other.x;
        }
};

class Vector3fix
{
    public:
        Fixed x;
        Fixed y;
        Fixed z;

        Vector3fix()
        {
            Vector3fix::x = 0;
            Vector3fix::y = 0;
            Vector3fix::z = 0;
        }
        Vector3fix(const Vector3fix& other)
        {
            Vector3fix::x = other.x;
            Vector3fix::y = other.y;
            Vector3fix::z = other.z;
        }
        Vector3fix(int x, int y, int z)
        {
            Vector3fix::x = Fixed(x);
            Vector3fix::y = Fixed(y);
            Vector3fix::z = Fixed(z);
        }
        Vector3fix(float x, float y, float z)
        {
            Vector3fix::x = Fixed(x);
            Vector3fix::y = Fixed(y);
            Vector3fix::z = Fixed(z);
        }
        Vector3fix(double x, double y, double z)
        {
            Vector3fix::x = Fixed(x);
            Vector3fix::y = Fixed(y);
            Vector3fix::z = Fixed(z);
        }
        Vector3fix(Fixed x, Fixed y, Fixed z)
        {
            Vector3fix::x = Fixed(x);
            Vector3fix::y = Fixed(y);
            Vector3fix::z = Fixed(z);
        }

        // Vector3fix on Vector3fix

        Vector3fix operator +(const Vector3fix &other)
        {
            return Vector3fix(x + other.x, y + other.y, z + other.z);
        }
        
        Vector3fix operator -(const Vector3fix &other)
        {
            return Vector3fix(x - other.x, y - other.y, z - other.z);
        }
        

        Vector3fix operator +=(const Vector3fix &other)
        {
            x += other.x;
            y += other.y;
            z += other.z;
            return *this;
        }
        
        Vector3fix operator -=(const Vector3fix &other)
        {
            x -= other.x;
            y -= other.y;
            z -= other.z;
            return *this;
        }


        // Vector3fix on float

        Vector3fix operator *(float other)
        {
            return Vector3fix(x * Fixed(other), y * Fixed(other), z * Fixed(other));
        }

        Vector3fix operator /(float other)
        {
            return Vector3fix(x / Fixed(other), y / Fixed(other), z / Fixed(other));
        }

        Vector3fix operator *=(float other)
        {
            x *= Fixed(other);
            y *= Fixed(other);
            z *= Fixed(other);
            return *this;
        }

        Vector3fix operator /=(float other)
        {
            x /= Fixed(other);
            y /= Fixed(other);
            z /= Fixed(other);
            return *this;
        }

        // Vector3fix on double

        Vector3fix operator *(double other)
        {
            return Vector3fix(x * Fixed(other), y * Fixed(other), z * Fixed(other));
        }

        Vector3fix operator /(double other)
        {
            return Vector3fix(x / Fixed(other), y / Fixed(other), z / Fixed(other));
        }

        Vector3fix operator *=(double other)
        {
            x *= Fixed(other);
            y *= Fixed(other);
            z *= Fixed(other);
            return *this;
        }

        Vector3fix operator /=(double other)
        {
            x /= Fixed(other);
            y /= Fixed(other);
            z /= Fixed(other);
            return *this;
        }

        // Vector3fix on Fixed

        Vector3fix operator *(Fixed other)
        {
            return Vector3fix(x * other, y * other, z * other);
        }

        Vector3fix operator /(Fixed other)
        {
            return Vector3fix(x / other, y / other, z / other);
        }

        Vector3fix operator *=(Fixed other)
        {
            x *= other;
            y *= other;
            z *= other;
            return *this;
        }

        Vector3fix operator /=(Fixed other)
        {
            x /= other;
            y /= other;
            z /= other;
            return *this;
        }

        // Vector3fix on int

        Vector3fix operator *(int other)
        {
            return Vector3fix(Fixed(x.value * other, true), Fixed(y.value * other, true), Fixed(z.value * other, true));
        }

        Vector3fix operator /(int other)
        {
            return Vector3fix(Fixed(x.value / other, true), Fixed(y.value / other, true), Fixed(z.value / other, true));
        }

        Vector3fix operator *=(int other)
        {
            x.value *= other;
            y.value *= other;
            z.value *= other;
            return *this;
        }

        Vector3fix operator /=(int other)
        {
            x.value /= other;
            y.value /= other;
            z.value /= other;
            return *this;
        }

        // Other

        Vector3fix operator =(const Vector3fix& other)
        {
            x = other.x;
            y = other.y;
            z = other.z;
            return *this;
        }

        Vector3fix operator +()
        {
            return Vector3fix(x, y, z);
        }

        Vector3fix operator -()
        {
            return Vector3fix(-x, -y, -z);
        }

        Fixed operator [](int index)
        {
            switch(index)
            {
                case 0:
                    return x;
                break;
                case 1:
                    return y;
                break;
                case 2:
                    return z;
                break;
                default:
                    return 0;
            }
        }

        bool operator ==(int all_equals)
        {
            if(x == Fixed(all_equals) && y == Fixed(all_equals) && z == Fixed(all_equals))
                return true;
            
            return false;
        }

        Vector3fix normalized()
        {
            Fixed inverse_len = Fixed::inverse_sqrt((x * x) + (y * y) + (z * z));
            return Vector3fix(x * inverse_len, y * inverse_len, z * inverse_len);
        }

        Fixed dot(const Vector3fix &other)
        {
            return x * other.x + y * other.y + z * other.z;
        }

        Vector3fix cross(const Vector3fix &other)
        {
            if(*this == 0 || Vector3fix(other) == 0)
            {
                panic("Tried to calculate cross product on 0 vector.");
                return Vector3fix(0, 0, 0);
            }
            Fixed new_x = y * other.z - z * other.y;
            Fixed new_y = z * other.x - x * other.z;
            Fixed new_z = x * other.y - y * other.x;
            return Vector3fix(new_x, new_y, new_z);
        }
};



#endif