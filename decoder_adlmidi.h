/***************************************************************************
 * This file is part of the TTK qmmp plugin project
 * Copyright (C) 2015 - 2025 Greedysky Studio

 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License along
 * with this program; If not, see <http://www.gnu.org/licenses/>.
 ***************************************************************************/

#ifndef DECODER_ADLMIDI_H
#define DECODER_ADLMIDI_H

#include <qmmp/decoder.h>

class AdlMidiHelper;

/*!
 * @author Greedysky <greedysky@163.com>
 */
class DecoderAdlMidi : public Decoder
{
public:
    explicit DecoderAdlMidi(const QString &path);
    virtual ~DecoderAdlMidi();

    static DecoderAdlMidi *instance();

    void readSettings();

    // Standard Decoder API
    virtual bool initialize() override final;
    virtual qint64 totalTime() const override final;
    virtual int bitrate() const override final;
    virtual qint64 read(unsigned char *data, qint64 maxSize) override final;
    virtual void seek(qint64 time) override final;

private:
    AdlMidiHelper *m_helper = nullptr;
    static DecoderAdlMidi *m_instance;

};

#endif
