#include "socketnotifier.h"
#include "private/abstracteventsource_p.h"

namespace zyppng {

class SocketNotifierPrivate : public AbstractEventSourcePrivate
{
  ZYPP_DECLARE_PUBLIC(SocketNotifier)
public:

  signal<void (const SocketNotifier &, int)> _activated;

  int _socket = -1;
  int _mode = SocketNotifier::Read;
  bool _enabled = false;

};

SocketNotifier::SocketNotifier (int socket, int evTypes , bool enable)
  : AbstractEventSource ( * new SocketNotifierPrivate )
{
  Z_D();
  d->_socket = socket;
  d->_mode = evTypes;

  setEnabled( enable );
}

SocketNotifier::Ptr SocketNotifier::create(int socket, int evTypes, bool enable )
{
  return std::shared_ptr<SocketNotifier>( new SocketNotifier( socket, evTypes, enable ) );
}

void SocketNotifier::setMode(int mode)
{
  Z_D();
  if ( mode == d->_mode )
    return;

  d->_mode = mode;

  if ( d->_enabled && d->_socket >= 0)
    updateFdWatch( d->_socket, d->_mode );
}

int SocketNotifier::mode() const
{
  return d_func()->_mode;
}

void SocketNotifier::setEnabled( bool enabled )
{
  Z_D();
  if ( enabled == d->_enabled || d->_socket < 0 )
    return;

  d->_enabled = enabled;

  if ( enabled )
    updateFdWatch( d->_socket, d->_mode );
  else
    removeFdWatch( -1 );
}

int SocketNotifier::socket() const
{
  return d_func()->_socket;
}

SignalProxy<void (const SocketNotifier &, int)> SocketNotifier::sigActivated()
{
  return d_func()->_activated;
}

void SocketNotifier::onFdReady( int, int events )
{
  d_func()->_activated( *this, events );
}

void SocketNotifier::onSignal( int )
{ }


}


