/*-
 *   BSD LICENSE
 *
 *   Copyright(c) 2010-2014 Intel Corporation. All rights reserved.
 *   All rights reserved.
 *
 *   Redistribution and use in source and binary forms, with or without
 *   modification, are permitted provided that the following conditions
 *   are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in
 *       the documentation and/or other materials provided with the
 *       distribution.
 *     * Neither the name of Intel Corporation nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef EAL_PCI_INIT_H_
#define EAL_PCI_INIT_H_

struct pci_map {
	void *addr;
	uint64_t offset;
	uint64_t size;
	uint64_t phaddr;
};

/*
 * For multi-process we need to reproduce all PCI mappings in secondary
 * processes, so save them in a tailq.
 */
struct mapped_pci_resource {
	TAILQ_ENTRY(mapped_pci_resource) next;

	struct rte_pci_addr pci_addr;
	char path[PATH_MAX];
	int nb_maps;
	struct pci_map maps[PCI_MAX_RESOURCE];
};

TAILQ_HEAD(mapped_pci_res_list, mapped_pci_resource);
extern struct mapped_pci_res_list *pci_res_list;

/*
 * Helper function to map PCI resources right after hugepages in virtual memory
 */
extern void *pci_map_addr;
void *pci_find_max_end_va(void);

void *pci_map_resource(void *requested_addr, int fd, off_t offset,
		size_t size);

/* map IGB_UIO resource prototype */
int pci_uio_map_resource(struct rte_pci_device *dev);

#endif /* EAL_PCI_INIT_H_ */
