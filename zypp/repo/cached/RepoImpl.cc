/*---------------------------------------------------------------------\
|                          ____ _   __ __ ___                          |
|                         |__  / \ / / . \ . \                         |
|                           / / \ V /|  _/  _/                         |
|                          / /__ | | | | | |                           |
|                         /_____||_| |_| |_|                           |
|                                                                      |
\---------------------------------------------------------------------*/

#include <iostream>
#include <map>

#include "zypp/base/Gettext.h"
#include "zypp/base/Logger.h"
#include "zypp/base/Measure.h"
#include "zypp/repo/cached/RepoImpl.h"
#include "zypp/cache/ResolvableQuery.h"

#include "zypp/sat/Pool.h"
#include "zypp/sat/Repo.h"
#include "zypp/sat/Solvable.h"

using namespace zypp::cache;
using namespace std;

///////////////////////////////////////////////////////////////////
namespace zypp
{ /////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
namespace repo
{ /////////////////////////////////////////////////////////////////
 ///////////////////////////////////////////////////////////////////
namespace cached
{ /////////////////////////////////////////////////////////////////

RepoImpl::RepoImpl( const RepoOptions &opts )
  : RepositoryImpl(opts.repoinfo)
  , _rquery(opts.solvdir)
  , _options(opts)
{
}

RepoImpl::~RepoImpl()
{
  MIL << "Destroying repo '" << info().alias() << "'" << endl;
}

void RepoImpl::createResolvables()
{
    sat::Pool satpool( sat::Pool::instance() );

    Pathname solvfile = (_options.solvdir + _options.repoinfo.alias()).extend(".solv");
    sat::Repo repo = satpool.addRepoSolv(solvfile, _options.repoinfo.alias() );

    if ( repo != sat::Repo::norepo )
    {
      sat::Repo::SolvableIterator it;
      for ( it = repo.solvablesBegin(); it != repo.solvablesEnd(); ++it )
      {
        _store.insert( makeResObject(*it) );
      }
    }
}

void RepoImpl::createPatchAndDeltas()
{

}

ResolvableQuery RepoImpl::resolvableQuery()
{
  return _rquery;
}


/////////////////////////////////////////////////////////////////
} // namespace cached
///////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
} // namespace repo
///////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
} // namespace zypp
///////////////////////////////////////////////////////////////////

