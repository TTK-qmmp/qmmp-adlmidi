#include "decoderadlmidifactory.h"
#include "adlmidimetadatamodel.h"
#include "decoder_adlmidi.h"
#include "adlmidihelper.h"
#include "settingsdialog.h"

#include <QMessageBox>

bool DecoderAdlMidiFactory::canDecode(QIODevice *input) const
{
    const QFile * const file = qobject_cast<QFile*>(input);
    if(!file)
    {
        return false;
    }

    AdlMidiHelper helper(file->fileName());
    return helper.initialize();
}

DecoderProperties DecoderAdlMidiFactory::properties() const
{
    DecoderProperties properties;
    properties.name = tr("AdlMidi Plugin");
    properties.shortName = "adlmidi";
    properties.filters << "*.mid" << "*.midi" << "*.mus" << "*.rmi" << "*.xmi";
    properties.description = "Midi File";
    properties.protocols << "file";
    properties.hasSettings = true;
    properties.noInput = true;
    properties.hasAbout = true;
    return properties;
}

Decoder *DecoderAdlMidiFactory::create(const QString &path, QIODevice *input)
{
    Q_UNUSED(input);
    return new DecoderAdlMidi(path);
}

QList<TrackInfo*> DecoderAdlMidiFactory::createPlayList(const QString &path, TrackInfo::Parts parts, QStringList *)
{
    TrackInfo *info = new TrackInfo(path);
    if(parts == TrackInfo::Parts())
    {
        return QList<TrackInfo*>() << info;
    }

    AdlMidiHelper helper(path);
    if(!helper.initialize())
    {
        delete info;
        return QList<TrackInfo*>();
    }

    if(parts & TrackInfo::MetaData)
    {
        info->setValue(Qmmp::TITLE, helper.title());
    }

    if(parts & TrackInfo::Properties)
    {
        info->setValue(Qmmp::BITRATE, helper.bitrate());
        info->setValue(Qmmp::SAMPLERATE, helper.sampleRate());
        info->setValue(Qmmp::CHANNELS, helper.channels());
        info->setValue(Qmmp::BITS_PER_SAMPLE, helper.depth());
        info->setValue(Qmmp::FORMAT_NAME, "AdlMidi");
        info->setDuration(helper.totalTime());
    }
    return QList<TrackInfo*>() << info;
}

MetaDataModel* DecoderAdlMidiFactory::createMetaDataModel(const QString &path, bool readOnly)
{
    Q_UNUSED(readOnly);
    return new AdlMidiMetaDataModel(path);
}

#if (QMMP_VERSION_INT < 0x10700) || (0x20000 <= QMMP_VERSION_INT && QMMP_VERSION_INT < 0x20200)
void DecoderAdlMidiFactory::showSettings(QWidget *parent)
{
    (new SettingsDialog(parent))->show();
}
#else
QDialog *DecoderAdlMidiFactory::createSettings(QWidget *parent)
{
    return new SettingsDialog(parent);
}
#endif

void DecoderAdlMidiFactory::showAbout(QWidget *parent)
{
    QMessageBox::about(parent, tr("About AdlMidi Reader Plugin"),
                       tr("Qmmp AdlMidi Reader Plugin") + "\n" +
                       tr("Written by: Greedysky <greedysky@163.com>"));
}

QString DecoderAdlMidiFactory::translation() const
{
    return QString();
}
