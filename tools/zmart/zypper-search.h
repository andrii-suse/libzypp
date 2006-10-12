/*-----------------------------------------------------------*- c++ -*-\
|                          ____ _   __ __ ___                          |
|                         |__  / \ / / . \ . \                         |
|                           / / \ V /|  _/  _/                         |
|                          / /__ | | | | | |                           |
|                         /_____||_| |_| |_|                           |
|                                                                      |
\---------------------------------------------------------------------*/


#ifndef ZYPPERSEARCH_H_
#define ZYPPERSEARCH_H_

#include <string>
#include <boost/regex.hpp>
#include <zypp/ZYpp.h>

#include "zypper-tabulator.h"

/**
 * @brief: search options
 */
class ZyppSearchOptions {
public:
  ZyppSearchOptions () :
    _installed_only(false), _uninstalled_only(false), _match_all(true), _kind(zypp::Resolvable::Kind()) {}
  
  bool installedOnly() const { return _installed_only; }
  bool uninstalledOnly() const { return _uninstalled_only; }
  bool matchAll() const { return _match_all; }
  bool matchAny() const { return !_match_all; }
  zypp::Resolvable::Kind kind() const { return _kind; }

  void setInstalledOnly(const bool installed_only = true) {
    _installed_only = installed_only;
  }
  void setUnInstalledOnly(const bool uninstalled_only = true) {
    _uninstalled_only = uninstalled_only;
  }
  void setMatchAll(const bool match_all = true) { _match_all = match_all; }
  void setMatchAny(const bool match_any = true) { _match_all = !match_any; }
  void setKind(const zypp::Resolvable::Kind & kind) { _kind = kind; }

private:
  bool _installed_only;
  bool _uninstalled_only;
  bool _match_all;
  zypp::Resolvable::Kind _kind;
};

/**
 *
 */
class ZyppSearch {
public:
  ZyppSearch (const ZyppSearchOptions & options, const vector<std::string> & qstrings = vector<string>());
  Table doSearch();

private:
  const ZyppSearchOptions & _options;
  const vector<std::string> & _qstrings;
  boost::regex _reg;

  bool init() const;
  void setupRegexp();
  bool match(const zypp::PoolItem & pool_item);
  TableRow createRow(const zypp::PoolItem & pool_item);
};


#endif /*ZYPPERSEARCH_H_*/
