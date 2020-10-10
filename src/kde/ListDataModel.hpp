/***************************************************************************
 * ROM Properties Page shell extension. (KDE4/KF5)                         *
 * ListDataModel.hpp: QAbstractListModel for RFT_LISTDATA.                 *
 *                                                                         *
 * Copyright (c) 2012-2020 by David Korth.                                 *
 * SPDX-License-Identifier: GPL-2.0-or-later                               *
 ***************************************************************************/

#ifndef __ROMPROPERTIES_KDE_LISTDATAMODEL_HPP__
#define __ROMPROPERTIES_KDE_LISTDATAMODEL_HPP__

// librpbase
#include "librpbase/RomFields.hpp"

// Qt includes.
#include <QtCore/QAbstractListModel>

class ListDataModelPrivate;
class ListDataModel : public QAbstractListModel
{
	Q_OBJECT
	typedef QAbstractListModel super;

	Q_PROPERTY(uint32_t lc READ lc WRITE setLC NOTIFY lcChanged)

	public:
		explicit ListDataModel(QObject *parent = 0);
		virtual ~ListDataModel();

	protected:
		ListDataModelPrivate *const d_ptr;
		Q_DECLARE_PRIVATE(ListDataModel)
	private:
		Q_DISABLE_COPY(ListDataModel)

	public:
		// Qt Model/View interface.
		int rowCount(const QModelIndex& parent = QModelIndex()) const final;
		int columnCount(const QModelIndex& parent = QModelIndex()) const final;

		QVariant data(const QModelIndex& index, int role) const final;
		QVariant headerData(int section, Qt::Orientation orientation, int role) const final;

		/**
		 * Set the field to use in this model.
		 * Field data is *copied* into the model.
		 * @param field Field.
		 */
		void setField(const LibRpBase::RomFields::Field *pField);

	public:
		/**
		 * Set the language code to use in this model.
		 * @param lc Language code. (0 for default)
		 */
		void setLC(uint32_t lc);

		/**
		 * Set the language code to use in this model.
		 * @param def_lc ROM default language code.
		 * @param user_lc User-specified language code.
		 */
		void setLC(uint32_t def_lc, uint32_t user_lc);

		/**
		 * Get the language code used in this model.
		 * @return Language code. (0 for default)
		 */
		uint32_t lc(void) const;

		/**
		 * Get all supported language codes.
		 *
		 * If this is not showing RFT_LISTDATA_MULTI, an empty vector
		 * will be returned.
		 *
		 * @return Supported language codes.
		 */
		std::vector<uint32_t> getLCs(void) const;

	signals:
		/**
		 * Language code has changed.
		 * @param lc Language code.
		 */
		void lcChanged(uint32_t lc);
};

#endif /* __MCRECOVER_MEMCARDMODEL_HPP__ */
