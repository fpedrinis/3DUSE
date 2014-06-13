////////////////////////////////////////////////////////////////////////////////
#include "dataprofile.hpp"
////////////////////////////////////////////////////////////////////////////////
namespace vcity
{
////////////////////////////////////////////////////////////////////////////////
DataProfile::DataProfile()
    : m_bboxLowerBound(), m_bboxUpperBound(), m_offset(), m_xStep(), m_yStep()
{

}
////////////////////////////////////////////////////////////////////////////////
DataProfile createDataProfileDefault()
{	
	return createDataProfileLyon();

	DataProfile dp;
    dp.m_offset.x = 0.0;
    dp.m_offset.y = 0.0;

    dp.m_xStep = 0;
    dp.m_yStep = 0;

    return dp;
}
////////////////////////////////////////////////////////////////////////////////
DataProfile createDataProfileParis()
{
    DataProfile dp;
    dp.m_offset.x = 643000.0;
    dp.m_offset.y = 6857000.0;

    dp.m_xStep = 500;
    dp.m_yStep = 500;

    return dp;
}
////////////////////////////////////////////////////////////////////////////////
DataProfile createDataProfileLyon()
{
    DataProfile dp;
    dp.m_offset.x = 1842500.0;//   1840000.0 		 1842500.0
    dp.m_offset.y = 5175800.0;//   5170000.0			 5175800.0

    dp.m_xStep = 0;
    dp.m_yStep = 0;

    return dp;
}
////////////////////////////////////////////////////////////////////////////////
} // namespace vcity
////////////////////////////////////////////////////////////////////////////////
