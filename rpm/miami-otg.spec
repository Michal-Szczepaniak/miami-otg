Name:       miami-otg

Summary:    OTG switch
Version:    0.1
Release:    1
License:    LICENSE
URL:        http://example.org/
Source0:    %{name}-%{version}.tar.bz2
Requires:   sailfishsilica-qt5 >= 0.10.9
BuildRequires:  pkgconfig(sailfishapp) >= 1.0.2
BuildRequires:  pkgconfig(Qt5Core)
BuildRequires:  pkgconfig(Qt5Qml)
BuildRequires:  pkgconfig(Qt5Quick)
BuildRequires:  pkgconfig(Qt5DBus)
BuildRequires:  desktop-file-utils

%description
OTG switch for miami


%prep
%setup -q -n %{name}-%{version}

%build

%qmake5 

%make_build

%post
systemctl daemon-reload >/dev/null 2>&1 || :
systemctl enable miami-otg.service >/dev/null 2>&1 || :

%install
%qmake5_install

%files
%defattr(-,root,root,-)
%{_bindir}/%{name}
%{_datadir}/jolla-settings/entries/otg.json
%{_datadir}/dbus-1/system.d
%{_datadir}/jolla-settings/pages/otg/EnableSwitch.qml
%{_datadir}/translations
%{_unitdir}/%{name}.service
