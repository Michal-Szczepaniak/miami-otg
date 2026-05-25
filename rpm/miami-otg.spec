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
BuildRequires:  desktop-file-utils

%description
OTG switch for miami


%prep
%setup -q -n %{name}-%{version}

%build

%qmake5 

%make_build

%post
%systemd_post miami-otg.service

%preun
%systemd_preun miami-otg.service

%postun
%systemd_postun_with_restart miami-otg.service

%install
%qmake5_install

%files
%defattr(-,root,root,-)
%{_bindir}/%{name}
%{_datadir}/jolla-settings/entries/otg.json
%{_datadir}/jolla-settings/pages/otg/EnableSwitch.qml
%{_unitdir}/%{name}.service
