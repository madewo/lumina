#Show the QML files to lupdate for translation purposes - not for the actual build
lupdate_only{
  SOURCES *= $${PWD}/RootDesktop.qml \
		$${PWD}/ContextMenu.qml \
		$${PWD}/Screen.qml \
		$${PWD}/Panel.qml
}

RESOURCES *= $${PWD}/src-qml.qrc
